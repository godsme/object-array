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

        using typename Self::Trait;
        using typename Self::Compare;

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

        template<typename ARG>
        auto Insert(ARG&& obj) -> auto* {
            Compare less{};
            if constexpr(std::is_trivially_copyable_v<ObjectType>) {
                for (int i = Num() - 2; i >= 0; --i) {
                    if (less(obj, GetObj(i))) continue;
                    return InsertAt(i+1, std::move(obj));
                }
                return InsertAt(0, std::move(obj));
            } else {
                for (int i = Num() - 2; i >= 0; --i) {
                    if (less(obj, GetObj(i))) {
                        Emplace(i + 1, std::move(obj));
                        Trait::Destroy(GetObj(i));
                    } else {
                       return Emplace(i+1, std::move(obj));
                    }
                }
                return Emplace(0, std::move(obj));
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

        template<typename ... ARGS>
        auto DoAppend(ARGS &&... args) -> ObjectType * {
            auto* p = Trait::Emplace(Elems()[Num()++], std::forward<ARGS>(args)...);
            if(Num() == 1) return p;

            Compare less{};
            for(int i = Num()-1; i>=0; i++) {
                if(!less(*p, GetObj(i))) break;
                std::swap(*p, GetObj(i));
            }

            return p;
        }

    public:
        template<typename ... ARGS>
        auto Append(ARGS &&... args) -> ObjectType * {
            return Num() < MAX_SIZE ? DoAppend(std::forward<ARGS>(args)...) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_ORDEREDAPPEND_H
