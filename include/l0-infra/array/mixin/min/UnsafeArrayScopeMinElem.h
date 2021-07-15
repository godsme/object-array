//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_393BC962688E4610918C23C1DF28DF90
#define OBJECT_ARRAY_2_393BC962688E4610918C23C1DF28DF90

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafeArrayScopeMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;
        using typename T::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeMinElemIndex(BitMap scope, LESS &&less) const -> Maybe {
            return T::Unsafe_RangeScopeMinElemIndex(0, T::Num(), scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeMinElem(BitMap scope, LESS &&less) const -> ObjectType const* {
            return T::Unsafe_RangeScopeMinElem(0, T::Num(), scope, std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_393BC962688E4610918C23C1DF28DF90
