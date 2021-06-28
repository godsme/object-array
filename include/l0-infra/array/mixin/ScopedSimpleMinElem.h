//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SCOPEDSIMPLEMINELEM_H
#define OBJECT_ARRAY_SCOPEDSIMPLEMINELEM_H

#include <l0-infra/array/mixin/ScopedMinElem.h>

namespace mixin {
    template<__cOnCePt(ConstScopedRangedArrayLike) T>
    class ScopedSimpleMinElem : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    protected:
        using Self::GetScope;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndex(LESS &&less) const -> auto {
            return Self::template DoMinElemIndex<false>(GetScope(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(LESS &&less) const -> auto* {
            return Self::template DoMinElem<false>(GetScope(), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSIMPLEMINELEM_H
