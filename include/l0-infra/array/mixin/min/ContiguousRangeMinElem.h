//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_CONTIGUOUSRANGEMINELEM_E11E5C15022548CA91328BD6AE7F0E5F
#define OBJECT_ARRAY_2_CONTIGUOUSRANGEMINELEM_E11E5C15022548CA91328BD6AE7F0E5F

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    class ContiguousRangeMinElem : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;
        using typename Self::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeMinElemIndex(SizeType from, SizeType until, LESS &&less) const -> Maybe {
            if(from >= until) return std::nullopt;
            SizeType min = from;
            for(auto i = from + 1; i < until; ++i) {
                if(less(T::GetObject(i), T::GetObject(min))) min = i;
            }
            return min;
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_RangeMinElem(SizeType from, SizeType until, LESS &&less) const -> ObjectType const* {
            if(from >= until) return nullptr;
            auto* end = &Self::GetObject(until);
            auto* p = std::min_element(&Self::GetObject(from), end, std::forward<LESS>(less));
            return p == end ? nullptr : p;
        }
    };
}

#endif //OBJECT_ARRAY_2_CONTIGUOUSRANGEMINELEM_E11E5C15022548CA91328BD6AE7F0E5F
