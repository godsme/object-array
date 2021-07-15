//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_D82188E4C71C4BA3BC5034DE90AB85C8
#define OBJECT_ARRAY_2_D82188E4C71C4BA3BC5034DE90AB85C8

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafePointersRangeSort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangePartialSort(SizeType from, SizeType until, LESS&& less, SizeType n) -> SizeType {
            return Self::GetPointers().Unsafe_RangePartialSort(from, until, Self::GetPointerLess(std::forward<LESS>(less)), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeSort(SizeType from, SizeType until, LESS&& less) -> void {
            Self::GetPointers().Unsafe_RangeSort(from, until, Self::GetPointerLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeStableSort(SizeType from, SizeType until, LESS&& less) -> void {
            Self::GetPointers().Unsafe_RangeStableSort(from, until, Self::GetPointerLess(std::forward<LESS>(less)));
        }
    };
}

#endif //OBJECT_ARRAY_2_D82188E4C71C4BA3BC5034DE90AB85C8
