//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_ARRAYLIKERANGESORT_H
#define OBJECT_ARRAY_ARRAYLIKERANGESORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/OrderedView.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<__cOnCePt(RangedArrayLike) T>
    struct ArrayLikeRangeSort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    protected:
        using typename Self::Owner;
        using typename T::RangedArrayLike;

    public:
        using Self::RangeSort;
        using Self::RangeStableSort;
        using Self::DoRangePartialSort;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(SizeType from, SizeType until, LESS&& less) & -> decltype(auto) {
            std::move(*this).RangeSort(from, until, std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(SizeType from, SizeType until, LESS&& less) & -> decltype(auto) {
            std::move(*this).RangeStableSort(from, until, std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(SizeType from, SizeType until, LESS&& less, SizeType n) & -> view::OrderedView<RangedArrayLike> {
            return {reinterpret_cast<RangedArrayLike&>(*this), DoRangePartialSort(from, until, std::forward<LESS>(less), n)};
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(SizeType from, SizeType until, LESS&& less, SizeType n) && -> void {
            DoRangePartialSort(from, until, std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYLIKERANGESORT_H
