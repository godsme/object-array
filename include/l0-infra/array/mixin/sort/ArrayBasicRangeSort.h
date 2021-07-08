//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_ARRAYBASICRANGESORT_H
#define OBJECT_ARRAY_ARRAYBASICRANGESORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/OrderedView.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<typename T>
    struct ArrayBasicRangeSort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        using Self::GetObj;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoRangePartialSort(SizeType from, SizeType until, LESS&& less, SizeType n) & -> SizeType {
            if(n == 0) return 0;
            if(n < (until - from)) {
                std::partial_sort(&GetObj(from), &GetObj(from) + n, &GetObj(until), std::forward<LESS>(less));
                return n;
            } else {
                std::move(*this).RangeSort(from, until, std::forward<LESS>(less));
                return until - from;
            }
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(SizeType from, SizeType until, LESS&& less) && -> void {
            std::sort(&GetObj(from), &GetObj(until), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(SizeType from, SizeType until, LESS&& less) && -> void {
            std::stable_sort(&GetObj(from), &GetObj(until), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYBASICRANGESORT_H
