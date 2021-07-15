//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_9C33E93CFD694EA6873F8D169E4F1B7A
#define OBJECT_ARRAY_2_9C33E93CFD694EA6873F8D169E4F1B7A

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafeScopeSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopePartialSort(BitMap scope, LESS&& less, SizeType n) -> SizeType {
            return T::Unsafe_RangeScopePartialSort(0, T::Num(), scope, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeSort(BitMap scope, LESS&& less) -> void {
            T::Unsafe_RangeScopeSort(0, T::Num(), scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeStableSort(BitMap scope, LESS&& less) -> void {
            T::Unsafe_RangeScopeStableSort(0, T::Num(), scope, std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_9C33E93CFD694EA6873F8D169E4F1B7A
