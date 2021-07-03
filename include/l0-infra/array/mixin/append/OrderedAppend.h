//
// Created by Darwin Yuan on 2021/7/2.
//

#ifndef OBJECT_ARRAY_ORDEREDAPPEND_H
#define OBJECT_ARRAY_ORDEREDAPPEND_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ContinuousArrayLikeDataHolder) T>
    class OrderedAppend : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::GetObj;
        using Self::Num;
        using Self::Elems;
        using Self::Less;

        using typename Self::Trait;

    private:
        template<typename ARG>
        auto Emplace(auto i, ARG&& obj) -> auto* {
            return Trait::Emplace(Elems()[i], std::move(obj));
        }

        template<typename ARG>
        auto InsertAt(auto i, ARG&& obj) -> auto* {
            auto num = Num() - i;
            if(num > 0) {
                ::memmove(Elems() + i + 1, Elems() + i, sizeof(ObjectType) * num);
            }
            return Emplace(i, std::move(obj));
        }

        template<typename OBJ>
        auto CopyInsert(OBJ&& obj) -> auto* {
            for (int i = Num() - 2; i >= 0; --i) {
                if (Less(obj, GetObj(i))) continue;
                return InsertAt(i+1, std::move(obj));
            }
            return InsertAt(0, std::move(obj));
        }

        template<typename ARG>
        auto NoCopyInsert(ARG&& obj) -> auto* {
            for (int i = Num() - 2; i >= 0; --i) {
                if (Less(obj, GetObj(i))) {
                    Emplace(i + 1, std::move(GetObj(i)));
                    Trait::Destroy(Elems()[i]);
                } else {
                    return Emplace(i+1, std::move(obj));
                }
            }
            return Emplace(0, std::move(obj));
        }

        template<typename OBJ>
        auto Insert(OBJ&& obj) -> auto* {
            if constexpr(std::is_trivially_copyable_v<ObjectType>) {
                return CopyInsert(std::forward<OBJ>(obj));
            } else {
                return NoCopyInsert(std::forward<OBJ>(obj));
            }
        }

        template<template<typename> typename TYPE_REF>
        auto ActualAppend(typename TYPE_REF<ObjectType>::type obj) -> ObjectType * {
            if(++Num() == 1) {
                return Emplace(0, std::move(obj));
            } else {
                return Insert(std::move(obj));
            }
        }

        auto DoAppend(ObjectType&& obj) -> ObjectType * {
            return ActualAppend<std::add_rvalue_reference>(std::move(obj));
        }

        template<typename OBJ>
        using add_const_reference = std::add_lvalue_reference<std::add_const_t<OBJ>>;

        auto DoAppend(ObjectType const& obj) -> ObjectType * {
            return ActualAppend<add_const_reference>(obj);
        }

        auto DoSort() -> auto* {
            for(int i = Num()-2; i>=0; --i) {
                if(!Less(GetObj(i+1), GetObj(i))) {
                    return &GetObj(i+1);
                }
                std::swap(GetObj(i+1), GetObj(i));
            }

            return &GetObj(0);
        }

        template<typename ... ARGS>
        auto DoAppend(ARGS &&... args) -> ObjectType * {
            auto* p = Trait::Emplace(Elems()[Num()++], std::forward<ARGS>(args)...);
            return Num() == 1 ? p : DoSort();
        }

    public:
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            return Num() < MAX_SIZE ? DoAppend(std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_ORDEREDAPPEND_H
