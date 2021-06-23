//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_ARRAYLIKE_H
#define OBJECT_ARRAY_ARRAYLIKE_H

#include <object-array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept {
    template<typename T>
    concept ConstArrayLike = SimpleConstArrayLike<T> && requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        typename T::ElemType;
        { o.GetRange() } -> std::same_as<typename T::SizeType>;
    };
}

#endif //OBJECT_ARRAY_ARRAYLIKE_H
