//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_1E20317D794F49B59F9FCED94485D9A3
#define OBJECT_ARRAY_2_1E20317D794F49B59F9FCED94485D9A3

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct UnsafePointerRangeFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindIndex(SizeType from, SizeType until, PRED&& pred) const -> Maybe {
            return T::GetPointers().Unsafe_RangeFindIndex(from, until, T::GetPointerPred(std::forward<PRED>(pred)));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFind(SizeType from, SizeType until, PRED&& pred) const -> ObjectType const* {
            auto* p = T::GetPointers().Unsafe_RangeFind(from, until, T::GetPointerPred(std::forward<PRED>(pred)));
            return p == nullptr ? nullptr : *p;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindRange(SizeType from, SizeType until, PRED&& pred) const -> auto {
            return T::GetPointers().Unsafe_RangeFindRange(from, until, T::GetPointerPred(std::forward<PRED>(pred)));
        }
    };
}

#endif //OBJECT_ARRAY_2_1E20317D794F49B59F9FCED94485D9A3
