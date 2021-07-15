//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_SIMPLERANGEFIND_18EF397B628D49A094362631E190F9E1
#define OBJECT_ARRAY_2_SIMPLERANGEFIND_18EF397B628D49A094362631E190F9E1

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class UnsafeRangeFind : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindIndex(SizeType from, SizeType until, PRED&& pred) const -> Maybe {
            if (from >= until) return std::nullopt;
            for (auto i = from; i < until; i++) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    if (pred(Self::GetObject(i), i)) return i;
                } else {
                    if (pred(Self::GetObject(i))) return i;
                }
            }
            return std::nullopt;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFind(SizeType from, SizeType until, PRED&& pred) const -> ObjectType const* {
            for (auto i = from; i < until; i++) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    if (pred(Self::GetObject(i), i)) return &Self::GetObject(i);
                } else {
                    if (pred(Self::GetObject(i))) return &Self::GetObject(i);
                }
            }
            return nullptr;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeFindRange(SizeType from, SizeType until, PRED&& pred) const -> std::pair<SizeType, SizeType> {
            auto begin = Unsafe_RangeFindIndex(from, until, std::forward<PRED>(pred));
            if(!begin) return {until, until};
            auto end = *begin + 1;
            for (; end < until; end++) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    if (!pred(Self::GetObject(end), end)) break;
                } else {
                    if (!pred(Self::GetObject(end))) break;
                }
            }
            return {*begin, end};
        }
    };
}

#endif //OBJECT_ARRAY_2_SIMPLERANGEFIND_18EF397B628D49A094362631E190F9E1
