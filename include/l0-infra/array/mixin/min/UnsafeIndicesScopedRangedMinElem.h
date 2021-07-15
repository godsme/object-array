//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_2901F19A673B4A5487AA113AE446915D
#define OBJECT_ARRAY_2_2901F19A673B4A5487AA113AE446915D

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafeIndicesScopedRangeMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;
        using typename T::BitMap;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeMinElemIndex(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> Maybe {
            return T::GetIndices().Unsafe_RangeScopeMinElemIndex(from, until, scope, T::GetIndicesLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeMinElem(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> ObjectType const* {
            auto* index = T::GetIndices().Unsafe_RangeScopeMinElem(from, until, scope, T::GetIndicesLess(std::forward<LESS>(less)));
            return index == nullptr ? nullptr : &T::GetArray().GetObject(*index);
        }
    };
}

#endif //OBJECT_ARRAY_2_2901F19A673B4A5487AA113AE446915D
