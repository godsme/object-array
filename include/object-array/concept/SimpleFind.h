//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_SIMPLEFIND_H
#define OBJECT_ARRAY_SIMPLEFIND_H

#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept {
    template<typename T>
    concept SimpleFind = requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        { o.FindIndex([](typename T::ObjectType const&) { return true; }) } -> std::same_as<std::optional<typename T::SizeType>>;
    };
}

#endif //OBJECT_ARRAY_SIMPLEFIND_H
