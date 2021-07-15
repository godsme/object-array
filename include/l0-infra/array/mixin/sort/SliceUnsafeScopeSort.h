//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_9A38DD0CB2F64217B4D2170573FF60F7
#define OBJECT_ARRAY_2_9A38DD0CB2F64217B4D2170573FF60F7

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct SliceUnsafeScopeSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopePartialSort(BitMap scope, LESS&& less, SizeType n) -> SizeType {
            return T::GetArray().Unsafe_RangeScopePartialSort(T::IndexBegin(), T::IndexEnd(), scope, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeSort(BitMap scope, LESS&& less) -> void {
            T::GetArray().Unsafe_RangeScopeSort(T::IndexBegin(), T::IndexEnd(), scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeStableSort(BitMap scope, LESS&& less) -> void {
            T::GetArray().Unsafe_RangeScopeStableSort(T::IndexBegin(), T::IndexEnd(), scope, std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_9A38DD0CB2F64217B4D2170573FF60F7
