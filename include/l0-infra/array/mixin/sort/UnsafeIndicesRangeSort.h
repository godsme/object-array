//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_INDEXEDARRAYLIKERANGESORT_5785CE2EB4714278B44110B53BC4DF2E
#define OBJECT_ARRAY_2_INDEXEDARRAYLIKERANGESORT_5785CE2EB4714278B44110B53BC4DF2E

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafeIndicesRangeSort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangePartialSort(SizeType from, SizeType until, LESS&& less, SizeType n) -> SizeType {
            return Self::GetIndices().Unsafe_RangePartialSort(from, until, Self::GetIndicesLess(std::forward<LESS>(less)), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeSort(SizeType from, SizeType until, LESS&& less) -> void {
            Self::GetIndices().Unsafe_RangeSort(from, until, Self::GetIndicesLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeStableSort(SizeType from, SizeType until, LESS&& less) -> void {
            Self::GetIndices().Unsafe_RangeStableSort(from, until, Self::GetIndicesLess(std::forward<LESS>(less)));
        }
    };
}

#endif //OBJECT_ARRAY_2_INDEXEDARRAYLIKERANGESORT_5785CE2EB4714278B44110B53BC4DF2E
