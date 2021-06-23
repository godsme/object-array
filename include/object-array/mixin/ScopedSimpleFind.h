//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDSIMPLEFIND_H
#define OBJECT_ARRAY_SCOPEDSIMPLEFIND_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/concept/Pred.h>
#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/mixin/ScopedFind.h>
#include <optional>
#include <algorithm>

namespace mixin {
    template<_concept::ConstScopedRangedArrayLike T>
    struct ScopedSimpleFind : detail::Extends<ScopedFind<T>> {
        using Self = detail::Extends<ScopedFind<T>>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

    private:
        using Self::GetScope;

    public:
        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindIndex(PRED&& pred) const -> std::optional<SizeType> {
            return Self::template FindIndex(GetScope(), std::forward<PRED>(pred));
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(PRED&& pred) const -> ObjectType const* {
            return Self::template Find(GetScope(), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSIMPLEFIND_H
