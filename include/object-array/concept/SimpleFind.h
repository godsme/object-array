//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_SIMPLEFIND_H
#define OBJECT_ARRAY_SIMPLEFIND_H

#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept {
    namespace detail {
        template<typename T>
        struct PredTypeTrait {
            using ObjectType = typename T::ObjectType;
            constexpr static auto pred = [](ObjectType const&) -> bool { return true; };
            using Type = decltype(pred);
        };

    }

    template<typename T>
    concept SimpleFind = requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        { o.FindIndex(std::declval<typename detail::PredTypeTrait<T>::Type>()) } -> std::same_as<std::optional<typename T::SizeType>>;
        { o.Find(std::declval<typename detail::PredTypeTrait<T>::Type>()) } -> std::same_as<typename T::ObjectType const*>;
    };
}

#endif //OBJECT_ARRAY_SIMPLEFIND_H
