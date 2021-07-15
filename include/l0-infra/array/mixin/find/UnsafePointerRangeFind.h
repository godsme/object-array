//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_1E20317D794F49B59F9FCED94485D9A3
#define OBJECT_ARRAY_2_1E20317D794F49B59F9FCED94485D9A3

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class UnsafePointerRangeFind : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    protected:
        template<__pRed_CoNcEpT(PRED)>
        auto GetPointerPred(PRED&& pred) -> auto {
            if constexpr(__wItH_iNdEx_pReD(PRED)) {
                return [&pred](auto* p, auto i) -> bool {
                    return pred(*p, i);
                };
            } else {
                return [&pred](auto* p) -> bool {
                    return pred(*p);
                };
            }
        }

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindIndex(SizeType from, SizeType until, PRED&& pred) const -> Maybe {
            return Self::GetPointer().Unsafe_RangeFindIndex(from, until, Self::GetPointerPred(std::forward<PRED>(pred)));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFind(SizeType from, SizeType until, PRED&& pred) const -> ObjectType const* {
            auto* p = Self::GetPointer().Unsafe_RangeFind(from, until, Self::GetPointerPred(std::forward<PRED>(pred)));
            return p == nullptr ? nullptr : *p;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindRange(SizeType from, SizeType until, PRED&& pred) const -> auto {
            return Self::GetPointer().Unsafe_RangeFindRange(from, until, Self::GetPointerPred(std::forward<PRED>(pred)));
        }
    };
}

#endif //OBJECT_ARRAY_2_1E20317D794F49B59F9FCED94485D9A3
