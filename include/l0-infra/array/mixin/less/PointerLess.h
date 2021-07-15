//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_7C21250993C443219BF6033B0D3B617F
#define OBJECT_ARRAY_7C21250993C443219BF6033B0D3B617F

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct PointerLess : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto GetPointerLess(LESS &&less) const -> auto {
            return [&](auto *l, auto *r) -> bool { return less(*l, *r); };
        }
    };
}

#endif //OBJECT_ARRAY_7C21250993C443219BF6033B0D3B617F
