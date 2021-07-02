//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_SIMPLEFIND_H
#define OBJECT_ARRAY_SIMPLEFIND_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/detail/PredTypeTrait.h>
#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept::detail {
    template<typename T>
    struct SimpleFindChecker : T {
        using T::FindIndex;
        using T::Find;
        using typename T::Maybe;
        using typename T::ObjectType;
    };

    template<typename T>
    concept SimpleFind = requires(T const& o, typename detail::PredTypeTrait<T> trait) {
        { o.FindIndex(trait.pred) } -> std::same_as<typename T::Maybe>;
        { o.Find(trait.pred) } -> std::same_as<typename T::ObjectType const*>;
    };
}

namespace _concept {
    template<typename T>
    concept SimpleFind = detail::SimpleFind<detail::SimpleFindChecker<T>>;
}

#endif

#endif //OBJECT_ARRAY_SIMPLEFIND_H
