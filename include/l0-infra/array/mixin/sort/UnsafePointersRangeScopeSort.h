//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_F408528F2C684207B397CE0D0B84FA20
#define OBJECT_ARRAY_2_F408528F2C684207B397CE0D0B84FA20


#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafePointersRangeScopeSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopePartialSort(SizeType from, SizeType until, BitMap scope, LESS&& less, SizeType n) -> SizeType {
            return T::GetPointers().Unsafe_RangeScopePartialSort(from, until, scope, T::GetPointerLess(std::forward<LESS>(less)), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeSort(SizeType from, SizeType until, BitMap scope, LESS&& less) -> void {
            T::GetPointers().Unsafe_RangeScopeSort(from, until, scope, T::GetPointerLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeStableSort(SizeType from, SizeType until, BitMap scope, LESS&& less) -> void {
            T::GetPointers().Unsafe_RangeScopeStableSort(from, until, scope, T::GetPointerLess(std::forward<LESS>(less)));
        }
    };
}

#endif //OBJECT_ARRAY_2_F408528F2C684207B397CE0D0B84FA20
