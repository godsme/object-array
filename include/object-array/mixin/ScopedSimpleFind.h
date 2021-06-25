//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDSIMPLEFIND_H
#define OBJECT_ARRAY_SCOPEDSIMPLEFIND_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/concept/Pred.h>
#include <object-array/mixin/ScopedFind.h>
#include <optional>
#include <algorithm>

namespace mixin {
    template<__cOnCePt(ConstScopedRangedArrayLike) T>
    struct ScopedSimpleFind : ScopedFind<T> {
        using Self = ScopedFind<T>;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        using Self::GetScope;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED&& pred) const -> Maybe {
            return Self::template DoFindIndex(GetScope(), std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED&& pred) const -> ObjectType const* {
            return Self::template DoFind(GetScope(), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSIMPLEFIND_H
