//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_ORDEREDAPPEND_DFF250D7B2A448A5B5D4E82316BE7E76
#define OBJECT_ARRAY_2_ORDEREDAPPEND_DFF250D7B2A448A5B5D4E82316BE7E76

namespace mixin {
    template<typename T>
    class OrderedAppend : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using T::Num;
        using T::Elems;
        using T::Emplace;
        using T::This;

    private:
        template<typename ARG>
        auto InsertAt(SizeType i, ARG&& obj) -> auto* {
            SizeType num = T::Num() - i - 1;
            if(num > 0) {
                ::memmove(Elems() + i + 1, Elems() + i, sizeof(ObjectType) * num);
            }
            return Self::Emplace(i, std::move(obj));
        }

        template<typename LESS, typename OBJ>
        auto CopyInsert(LESS&& less, OBJ&& obj) -> auto* {
            for (int i = Num() - 2; i >= 0; --i) {
                if (less(obj, Self::GetObject(i))) continue;
                return InsertAt(i+1, std::move(obj));
            }
            return InsertAt(0, std::move(obj));
        }

        template<typename LESS, typename ARG>
        auto NoCopyInsert(LESS&& less, ARG&& obj) -> auto* {
            for (int i = Num() - 2; i >= 0; --i) {
                if (less(obj, Self::GetObject(i))) {
                    Emplace(i + 1, std::move(Self::GetObject(i)));
                    Self::Destroy(i);
                } else {
                    return Emplace(i+1, std::move(obj));
                }
            }
            return Emplace(0, std::move(obj));
        }

        template<typename LESS, typename OBJ>
        auto Insert(LESS&& less, OBJ&& obj) -> auto* {
            if constexpr(std::is_trivially_copyable_v<ObjectType>) {
                return CopyInsert(std::forward<LESS>(less), std::forward<OBJ>(obj));
            } else {
                return NoCopyInsert(std::forward<LESS>(less), std::forward<OBJ>(obj));
            }
        }

        template<template<typename> typename TYPE_REF, typename LESS>
        auto ActualAppend(LESS&& less, typename TYPE_REF<ObjectType>::type obj) -> ObjectType * {
            if(++Num() == 1) {
                return Emplace(0, std::move(obj));
            } else {
                return Insert(std::forward<LESS>(less), std::move(obj));
            }
        }

        template<typename OBJ>
        using add_const_reference = std::add_lvalue_reference<std::add_const_t<OBJ>>;

        template<typename LESS>
        auto DoSort(LESS&& less) -> auto* {
            for(int i = Num()-2; i>=0; --i) {
                if(!less(Self::GetObject(i+1), Self::GetObject(i))) {
                    return &Self::GetObject(i+1);
                }
                std::swap(Self::GetObject(i+1), Self::GetObject(i));
            }

            return &Self::GetObject(0);
        }

    private:
        template<typename LESS>
        auto DoAppend(LESS&& less, ObjectType&& obj) -> ObjectType * {
            return ActualAppend<std::add_rvalue_reference>(std::forward<LESS>(less), std::move(obj));
        }

        template<typename LESS>
        auto DoAppend(LESS&& less, ObjectType const& obj) -> ObjectType * {
            return ActualAppend<add_const_reference>(std::forward<LESS>(less), obj);
        }

        template<typename LESS, typename ... ARGS>
        auto DoAppend(LESS&& less, ARGS &&... args) -> ObjectType * {
            auto* p = Self::Emplace(Num()++, std::forward<ARGS>(args)...);
            return Num() == 1 ? p : DoSort(std::forward<LESS>(less));
        }

    public:
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            if(T::All()) {
                return T::ReplaceLastIf(std::forward<ARGS>(args)...);
            } else {
                return DoAppend(T::GetLess(), std::forward<ARGS>(args)...);
            }
        }

        template<typename ... ARGS>
        auto Append_I(ARGS &&... args) -> Maybe {
            return T::ObjectToIndex(Append(std::forward<ARGS>(args)...));
        }
    };
}

#endif //OBJECT_ARRAY_2_ORDEREDAPPEND_DFF250D7B2A448A5B5D4E82316BE7E76
