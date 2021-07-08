//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_VIEWBASICRANGESORT_H
#define OBJECT_ARRAY_VIEWBASICRANGESORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/OrderedView.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<__cOnCePt(RangedArrayLike) T>
    struct ViewBasicRangeSort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    protected:
        using Self::GetArray;
        using Self::IS_ORDERED;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoRangePartialSort(SizeType from, SizeType until, LESS&& less, SizeType n) & -> SizeType {
            return GetArray().DoRangePartialSort(from, until, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(SizeType from, SizeType until, LESS&& less) && -> void {
            std::move(GetArray()).RangeSort(from, until, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(SizeType from, SizeType until, LESS&& less) && -> void {
            std::move(GetArray()).RangeStableSort(from, until, std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_VIEWBASICRANGESORT_H
