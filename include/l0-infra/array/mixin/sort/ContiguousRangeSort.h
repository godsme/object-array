//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_CONTIGUOUSARRAYLIKERANGESORT_H
#define OBJECT_ARRAY_2_CONTIGUOUSARRAYLIKERANGESORT_H

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ContiguousRangeSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangePartialSort(SizeType from, SizeType until, LESS&& less, SizeType n) -> SizeType {
            if(from >= until or n == 0) return 0;
            if(n < (until - from)) {
                auto* begin = &T::GetObject(from);
                std::partial_sort(begin, begin + n, &T::GetObject(until), std::forward<LESS>(less));
                return n;
            } else {
                Unsafe_RangeSort(from, until, std::forward<LESS>(less));
                return until - from;
            }
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeSort(SizeType from, SizeType until, LESS&& less) -> void {
            if(from >= until) return;
            std::sort(&T::GetObject(from), &T::GetObject(until), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeStableSort(SizeType from, SizeType until, LESS&& less) -> void {
            if(from >= until) return;
            std::stable_sort(&T::GetObject(from), &T::GetObject(until), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_CONTIGUOUSARRAYLIKERANGESORT_H
