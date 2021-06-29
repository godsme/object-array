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
    template<typename T>
    struct SimpleMinElemChecker : T {
        using T::MinElemIndex;
        using T::MinElem;
        using typename T::Maybe;
        using typename T::ObjectType;
    };

    template<typename T>
    concept SimpleMinElem = requires(SimpleMinElemChecker<T> const& o) {
        { o.MinElemIndex(std::declval<typename detail::LessTypeTrait<T>::Type&&>()) } -> std::same_as<typename SimpleMinElemChecker<T>::Maybe>;
        { o.MinElem(std::declval<typename detail::LessTypeTrait<T>::Type&&>()) } -> std::same_as<typename SimpleMinElemChecker<T>::ObjectType const*>;
    };
}
#endif

#endif //OBJECT_ARRAY_CONCEPT_SIMPLEMINELEM_H
