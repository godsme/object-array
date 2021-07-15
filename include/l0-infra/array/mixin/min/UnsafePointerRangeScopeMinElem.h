//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_CE031144C91945768C30CFE5ECE03F78
#define OBJECT_ARRAY_2_CE031144C91945768C30CFE5ECE03F78

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafePointerScopedRangeMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeMinElemIndex(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> Maybe {
            return T::GetPointers().Unsafe_RangeScopeMinElemIndex(from, until, scope, T::GetPointerLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeMinElem(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> ObjectType const* {
            auto* p = T::GetPointers().Unsafe_RangeScopeMinElem(from, until, scope, T::GetPointerLess(std::forward<LESS>(less)));
            return p == nullptr ? nullptr : *p;
        }
    };
}
#endif //OBJECT_ARRAY_2_CE031144C91945768C30CFE5ECE03F78
