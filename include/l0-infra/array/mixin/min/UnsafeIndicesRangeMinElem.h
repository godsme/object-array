//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_B7B407AAC6ED41828A3E6C06043AB7C1
#define OBJECT_ARRAY_2_B7B407AAC6ED41828A3E6C06043AB7C1

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    class UnsafeIndicesRangeMinElem : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;
        using typename Self::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeMinElemIndex(SizeType from, SizeType until, LESS &&less) const -> Maybe {
            return Self::GetIndices().Unsafe_RangeMinElemIndex(from, until, Self::GetIndicesLess(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeMinElem(SizeType from, SizeType until, LESS &&less) const -> ObjectType const* {
            auto* index = Self::GetIndices().Unsafe_RangeMinElem(from, until, Self::GetIndicesLess(std::forward<LESS>(less)));
            return index == nullptr ? nullptr : &Self::GetArray().GetObject(*index);
        }
    };
}

#endif //OBJECT_ARRAY_2_B7B407AAC6ED41828A3E6C06043AB7C1
