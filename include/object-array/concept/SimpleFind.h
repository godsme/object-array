//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_SIMPLEFIND_H
#define OBJECT_ARRAY_SIMPLEFIND_H

#include <object-array/concept/detail/PredTypeTrait.h>
#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept {
    template<typename T>
    concept SimpleFind = requires(T const& o) {
        { o.FindIndex(std::declval<typename detail::PredTypeTrait<T>::Type>()) } -> std::same_as<typename T::Maybe>;
        { o.Find(std::declval<typename detail::PredTypeTrait<T>::Type>()) } -> std::same_as<typename T::ObjectType const*>;
    };
}

#endif //OBJECT_ARRAY_SIMPLEFIND_H
