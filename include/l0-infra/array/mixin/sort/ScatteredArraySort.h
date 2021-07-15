//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_6A7A4913BC6C4C2B8776DD21DE517753
#define OBJECT_ARRAY_2_6A7A4913BC6C4C2B8776DD21DE517753

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ScatteredArraySort : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoSort(LESS&& less) -> void {
            T::Unsafe_RangeScopeSort(0, T::MAX_SIZE, T::GetScope(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoStableSort(LESS&& less) -> void {
            T::Unsafe_RangeScopeStableSort(0, T::MAX_SIZE, T::GetScope(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) -> SizeType {
            return T::Unsafe_RangeScopePartialSort(0, T::MAX_SIZE, T::GetScope(), std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_2_6A7A4913BC6C4C2B8776DD21DE517753
