//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_CONCEPT_SIMPLEMINELEM_H
#define OBJECT_ARRAY_CONCEPT_SIMPLEMINELEM_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/detail/LessTypeTrait.h>
#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept {
    namespace detail {
        template<typename T>
        struct SimpleMinElemChecker : T {
            using T::MinElemIndex;
            using T::MinElem;
            using typename T::Maybe;
            using typename T::ObjectType;
        };

        template<typename T>
        concept SimpleMinElem = requires(T const& o, typename detail::LessTypeTrait<T> trait) {
            { o.MinElemIndex(trait.less) } -> std::same_as<typename T::Maybe>;
            { o.MinElem(trait.less) } -> std::same_as<typename T::ObjectType const*>;
        };
    }

    template<typename T>
    concept SimpleMinElem = detail::SimpleMinElem<detail::SimpleMinElemChecker<T>>;
}

#endif

#endif //OBJECT_ARRAY_CONCEPT_SIMPLEMINELEM_H
