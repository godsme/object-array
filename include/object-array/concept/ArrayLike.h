//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_ARRAYLIKE_H
#define OBJECT_ARRAY_ARRAYLIKE_H

#include <object-array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept {
    template<typename T>
    concept ConstArrayLike = requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        typename T::ElemType;
        { o.Elems() } -> std::same_as<typename T::ElemType const*>;
        { T::ElemToObject(std::declval<typename T::ElemType const&>()) } -> std::same_as<typename T::ObjectType const&>;
        { o.GetRange() } -> std::same_as<typename T::SizeType>;
    };
}

#endif //OBJECT_ARRAY_ARRAYLIKE_H
