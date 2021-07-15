//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_SCOPEDRANGEFIND_34A1A1D7D1DF4BF6B07F1CDBE5E54EA0
#define OBJECT_ARRAY_2_SCOPEDRANGEFIND_34A1A1D7D1DF4BF6B07F1CDBE5E54EA0

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class UnsafeScopedRangeFind : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;
        using typename T::BitMap;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeScopeFindIndex(SizeType from, SizeType until, BitMap scope, PRED&& pred) const -> Maybe {
            return Self::Unsafe_RangeFindIndex(from, until, [scope, &pred](auto&& obj, SizeType i) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    return scope[i] && pred(obj, i);
                } else {
                    return scope[i] && pred(obj);
                }
            });
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_RangeScopeFind(SizeType from, SizeType until, BitMap scope, PRED&& pred) const -> ObjectType const* {
            return Self::Unsafe_RangeFind(from, until, [scope, &pred](auto&& obj, SizeType i) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    return scope[i] && pred(obj, i);
                } else {
                    return scope[i] && pred(obj);
                }
            });
        }
    };
}

#endif //OBJECT_ARRAY_2_SCOPEDRANGEFIND_34A1A1D7D1DF4BF6B07F1CDBE5E54EA0
