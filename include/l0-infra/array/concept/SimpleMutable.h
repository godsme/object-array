//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTABLE_H
#define OBJECT_ARRAY_SIMPLEMUTABLE_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/detail/PredTypeTrait.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/concept/SimpleFind.h>
#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept {
    namespace detail {
        template<typename T>
        struct SimpleMutableChecker : T {
            using T::Erase;
            using T::Append;

            using typename T::SizeType;
            using typename T::ObjectType;
        };

        template<typename T>
        concept SimpleMutable = requires(T& o, typename T::ObjectType const& obj, typename T::ObjectType&& r_obj) {
            { o.Erase(typename T::SizeType{}) };
            { o.Append() } -> std::same_as<typename T::ObjectType*>;
            { o.Append(obj) } -> std::same_as<typename T::ObjectType*>;
            { o.Append(r_obj) } -> std::same_as<typename T::ObjectType*>;
        };
    }

    template<typename T>
    concept SimpleMutable = detail::SimpleMutable<detail::SimpleMutableChecker<std::decay_t<T>>>;

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
