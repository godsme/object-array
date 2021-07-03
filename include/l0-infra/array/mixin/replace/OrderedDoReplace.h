//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_ORDEREDDOREPLACE_H
#define OBJECT_ARRAY_ORDEREDDOREPLACE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>
#include <l0-infra/array/mixin/erase/SimpleDoErase.h>

namespace mixin {
    template<typename T>
    class OrderedDoReplace : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using Self::Elems;
        using Self::GetObj;

    private:
        template<typename LESS>
        auto LeftMove(LESS&& less, SizeType i) -> auto* {
            do {
                std::swap(GetObj(i), GetObj(i-1));
                --i;
            } while(i > 0 && less(GetObj(i), GetObj(i-1)));

            return &GetObj(i);
        }

        template<typename LESS>
        auto RightMove(LESS&& less, SizeType i) -> auto* {
            auto boundary = Self::Num() - 1;
            do {
                std::swap(GetObj(i), GetObj(i+1));
                ++i;
            } while(i < boundary && !less(GetObj(i), GetObj(i+1)));

            return &GetObj(i);
        }

    public:
        template<typename LESS, typename ... ARGS>
        auto ActualReplace(LESS&& less, SizeType i, ARGS&& ... args) -> ObjectType* {
            auto* p = Self::Trait::Replace(Elems()[i], std::forward<ARGS>(args)...);
            if(i > 0 && less(GetObj(i), GetObj(i-1))) {
                return LeftMove(std::forward<LESS>(less), i);
            } else if(i < (Self::Num() - 1) && !less(GetObj(i), GetObj(i+1))) {
                return RightMove(std::forward<LESS>(less), i);
            } else {
                return p;
            }
        }
    };
}

#endif //OBJECT_ARRAY_ORDEREDDOREPLACE_H
