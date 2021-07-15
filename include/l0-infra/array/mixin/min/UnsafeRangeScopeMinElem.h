//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_SCOPEDRANGEMINELEM_EED7E8E361AF498898DD9BF9B0DC53C3
#define OBJECT_ARRAY_2_SCOPEDRANGEMINELEM_EED7E8E361AF498898DD9BF9B0DC53C3

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    class UnsafeRangeScopeMinElem : public T {
        using Self = T;

    public:
        using typename Self::Maybe;
        using typename Self::BitMap;
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeMinElemIndex(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> Maybe {
            if(scope.none()) return std::nullopt;

            for (; from < until; ++from) if (scope.TestAndClear(from)) break;
            for (auto i = from+1; scope.any() && i < until; ++i) {
                if (scope.TestAndClear(i) && less(Self::GetObject(i), Self::GetObject(from))) from = i;
            }
            return from;
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeScopeMinElem(SizeType from, SizeType until, BitMap scope, LESS &&less) const -> ObjectType const* {
            auto index = Unsafe_RangeScopeMinElemIndex(from, until, scope, std::forward<LESS>(less));
            return index ? &Self::GetObject(*index) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_2_SCOPEDRANGEMINELEM_EED7E8E361AF498898DD9BF9B0DC53C3
