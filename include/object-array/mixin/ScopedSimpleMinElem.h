//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SCOPEDSIMPLEMINELEM_H
#define OBJECT_ARRAY_SCOPEDSIMPLEMINELEM_H

#include <object-array/mixin/ScopedMinElem.h>

namespace mixin {
    template<_concept::ConstScopedRangedArrayLike T>
    struct ScopedSimpleMinElem : ScopedMinElem<T> {
        using Self = ScopedMinElem<T>;
    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    public:
        using Self::GetScope;

    public:
        template<_concept::Less<ObjectType> LESS>
        auto MinElemIndex(LESS &&less) const -> auto {
            return Self::template DoMinElemIndex<false>(GetScope(), std::forward<LESS>(less));
        }

        template<_concept::Less<ObjectType> LESS>
        auto MinElem(LESS &&less) const -> auto* {
            return Self::template DoMinElem<false>(GetScope(), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSIMPLEMINELEM_H
