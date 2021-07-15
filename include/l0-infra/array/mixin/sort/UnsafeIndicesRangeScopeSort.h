//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_46D764504BFF4F30AC12A65BDB2EE2DA
#define OBJECT_ARRAY_2_46D764504BFF4F30AC12A65BDB2EE2DA

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafeIndicesRangeScopeSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopePartialSort(SizeType from, SizeType until, BitMap scope, LESS&& less, SizeType n) -> SizeType {
            return T::GetIndices().Unsafe_RangeScopePartialSort(from, until, scope, T::GetIndicesLess(std::forward<LESS>(less)), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeSort(SizeType from, SizeType until, BitMap scope, LESS&& less) -> void {
            T::GetIndices().Unsafe_RangeScopeSort(from, until, scope, T::GetIndicesLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeStableSort(SizeType from, SizeType until, BitMap scope, LESS&& less) -> void {
            T::GetIndices().Unsafe_RangeScopeStableSort(from, until, scope, T::GetIndicesLess(std::forward<LESS>(less)));
        }
    };
}

#endif //OBJECT_ARRAY_2_46D764504BFF4F30AC12A65BDB2EE2DA
