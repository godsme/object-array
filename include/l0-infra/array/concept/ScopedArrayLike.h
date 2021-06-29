//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDARRAYLIKE_H
#define OBJECT_ARRAY_SCOPEDARRAYLIKE_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/concept/ArrayLike.h>
#include <l0-infra/array/concept/ElemVisitor.h>

namespace _concept {

    namespace detail {
        template<typename T>
        struct ScopedChecker : T {
            using T::GetScope;
            using typename T::BitMap;
        };

        template<typename T>
        concept Scoped = requires(T const& o) {
            { o.GetScope() } -> std::same_as<typename T::BitMap>;
        };
    }

    template<typename T>
    concept Scoped = detail::Scoped<detail::ScopedChecker<T>>;

    template<typename T>
    concept ConstScopedArrayLike = Scoped<T> && ConstArrayLike<T>;

    template<typename T>
    concept ConstScopedRangedArrayLike = Scoped<T> && ConstRangedArrayLike<T>;

    template<typename T>
    concept ScopedRangedArrayLike = Scoped<T> && RangedArrayLike<T>;

    template<typename T>
    concept SimpleScopedRangedArrayLike = Scoped<T> && SimpleRangedArrayLike<T>;

    template<typename T>
    concept ScopedOpVisitable = Scoped<T> && OpVisitable<T>;
}

#endif

#endif //OBJECT_ARRAY_SCOPEDARRAYLIKE_H
