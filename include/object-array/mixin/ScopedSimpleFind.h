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
    template<_concept::ConstScopedRangedArrayLike T>
    struct ScopedSimpleFind : ScopedFind<T> {
        using Self = ScopedFind<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using Maybe = typename T::Maybe;

    private:
        using Self::GetScope;

    public:
        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindIndex(PRED&& pred) const -> Maybe {
            return Self::template DoFindIndex(GetScope(), std::forward<PRED>(pred));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(PRED&& pred) const -> ObjectType const* {
            return Self::template DoFind(GetScope(), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSIMPLEFIND_H
