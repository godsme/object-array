//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_ORDEREDDOAPPEND_H
#define OBJECT_ARRAY_ORDEREDDOAPPEND_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ContiguousArrayLikeDataHolder) T>
    class OrderedDoAppend : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        static constexpr auto MAX_SIZE = T::MAX_SIZE;

    protected:
        using Self::GetObj;
        using Self::Num;
        using Self::Elems;

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

        template<typename LESS, typename OBJ>
        auto CopyInsert(LESS&& less, OBJ&& obj) -> auto* {
            for (int i = Num() - 2; i >= 0; --i) {
                if (less(obj, GetObj(i))) continue;
                return InsertAt(i+1, std::move(obj));
            }
            return InsertAt(0, std::move(obj));
        }

        template<typename LESS, typename ARG>
        auto NoCopyInsert(LESS&& less, ARG&& obj) -> auto* {
            for (int i = Num() - 2; i >= 0; --i) {
                if (less(obj, GetObj(i))) {
                    Emplace(i + 1, std::move(GetObj(i)));
                    Trait::Destroy(Elems()[i]);
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
                if(!less(GetObj(i+1), GetObj(i))) {
                    return &GetObj(i+1);
                }
                std::swap(GetObj(i+1), GetObj(i));
            }

            return &GetObj(0);
        }

    public:
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
            auto* p = Trait::Emplace(Elems()[Num()++], std::forward<ARGS>(args)...);
            return Num() == 1 ? p : DoSort(std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_ORDEREDDOAPPEND_H
