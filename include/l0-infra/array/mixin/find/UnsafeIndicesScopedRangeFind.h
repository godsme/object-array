//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_7DEA0D9B9BAA4119BC61018B6C5B2C18
#define OBJECT_ARRAY_2_7DEA0D9B9BAA4119BC61018B6C5B2C18

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class UnsafeIndicesScopedRangeFind : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;
        using typename T::BitMap;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeScopeFindIndex(SizeType from, SizeType until, BitMap scope, PRED&& pred) const -> Maybe {
            return Self::GetIndices().Unsafe_RangeScopeFindIndex(from, until, scope, Self::GetIndicesPred(std::forward<PRED>(pred)));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeScopeFind(SizeType from, SizeType until, BitMap scope, PRED&& pred) const -> ObjectType const* {
            auto* index = Self::GetIndices().Unsafe_RangeScopeFind(from, until, scope, Self::GetIndicesPred(std::forward<PRED>(pred)));
            return index == nullptr ? nullptr : T::GetArray().At(*index);
        }
    };
}

#endif //OBJECT_ARRAY_2_7DEA0D9B9BAA4119BC61018B6C5B2C18
