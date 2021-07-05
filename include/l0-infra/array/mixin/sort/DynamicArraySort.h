//
// Created by Darwin Yuan on 2021/7/6.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAYSORT_H
#define OBJECT_ARRAY_DYNAMICARRAYSORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/OrderedView.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<typename T>
    struct DynamicArraySort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    protected:
        using typename Self::Owner;
        using typename T::RangedArrayLike;

        using Self::GetPointers;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) & -> SizeType {
            return GetPointers().DoPartialSort([&](auto* l, auto* r) {
                return less(*l, *r);
            }, n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && -> void {
            GetPointers().Sort([&](auto* l, auto* r) {
                return less(*l, *r);
            });
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) & -> decltype(auto) {
            std::move(*this).Sort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && -> void {
            GetPointers().StableSort([&](auto* l, auto* r) {
                return less(*l, *r);
            });
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) & -> decltype(auto) {
            std::move(*this).StableSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) & -> view::OrderedView<RangedArrayLike> {
            return {reinterpret_cast<RangedArrayLike&>(*this), DoPartialSort(std::forward<LESS>(less), n)};
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> void {
            DoPartialSort(std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_DYNAMICARRAYSORT_H
