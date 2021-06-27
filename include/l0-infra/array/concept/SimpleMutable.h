//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTABLE_H
#define OBJECT_ARRAY_SIMPLEMUTABLE_H

#include <l0-infra/array/detail/config.h>
#include <l0-infra/array/concept/detail/ConceptDef.h>
#if HAS_CONCEPT
#include <l0-infra/array/concept/detail/PredTypeTrait.h>
#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept {
    template<typename T>
    concept SimpleMutable = requires(T& o) {
        { o.Erase(typename T::SizeType{}) };
        { o.Append() } -> std::same_as<typename T::ObjectType*>;
        { o.Append(std::declval<typename T::ObjectType const&>()) } -> std::same_as<typename T::ObjectType*>;
        { o.Append(std::declval<typename T::ObjectType&&>()) } -> std::same_as<typename T::ObjectType*>;
    };

    template<typename T>
    concept SimpleRangedMutable = _concept::SimpleMutable<T> && _concept::SimpleRangedArrayLike<T>;

    template<typename T>
    concept SimpleFindMutable =
            _concept::SimpleRangedArrayLike<T> &&
            _concept::SimpleMutable<T> &&
            _concept::SimpleFind<T>;
}
#endif

#endif //OBJECT_ARRAY_SIMPLEMUTABLE_H
