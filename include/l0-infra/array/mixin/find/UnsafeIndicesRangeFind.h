//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_DD3EBD8AA50B4AE999F3E5B40A79DFF7
#define OBJECT_ARRAY_2_DD3EBD8AA50B4AE999F3E5B40A79DFF7

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct UnsafeIndicesRangeFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindIndex(SizeType from, SizeType until, PRED&& pred) const -> Maybe {
            return T::GetIndices().Unsafe_RangeFindIndex(from, until, T::GetIndicesPred(std::forward<PRED>(pred)));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFind(SizeType from, SizeType until, PRED&& pred) const -> ObjectType const* {
            auto* index = T::GetIndices().Unsafe_RangeFind(from, until, T::GetIndicesPred(std::forward<PRED>(pred)));
            return index == nullptr ? nullptr : &T::GetObject(*index);
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindRange(SizeType from, SizeType until, PRED&& pred) const -> auto {
            return T::GetIndices().Unsafe_RangeFindRange(from, until, T::GetIndicesPred(std::forward<PRED>(pred)));
        }
    };
}

#endif //OBJECT_ARRAY_2_DD3EBD8AA50B4AE999F3E5B40A79DFF7
