//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_B16413FA2B49458193D61886EF6E6956
#define OBJECT_ARRAY_2_B16413FA2B49458193D61886EF6E6956

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/detail/ScopedArrayIndices.h>
#include <algorithm>

namespace mixin {
    template<typename T>
    struct UnsafeRangeScopeSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopePartialSort(SizeType from, SizeType until, BitMap scope, LESS&& less, SizeType n) -> SizeType {
            if(n == 0) return 0;
            ::detail::ScopedArrayIndices indices{T::ToThisType(), from, until, scope};
            if(n < indices.GetNum()) {
                std::partial_sort(indices.begin(), indices.begin() + n, indices.end(), std::forward<LESS>(less));
                return n;
            } else {
                std::sort(indices.begin(), indices.end(), std::forward<LESS>(less));
                return indices.GetNum();
            }
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeSort(SizeType from, SizeType until, BitMap scope, LESS&& less) -> void {
            ::detail::ScopedArrayIndices indices{T::ToThisType(), from, until, scope};
            std::sort(indices.begin(), indices.end(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeStableSort(SizeType from, SizeType until, BitMap scope, LESS&& less) -> void {
            ::detail::ScopedArrayIndices indices{T::ToThisType(), from, until, scope};
            std::stable_sort(indices.begin(), indices.end(), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_B16413FA2B49458193D61886EF6E6956
