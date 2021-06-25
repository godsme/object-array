//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_ARRAYLIKE_H
#define OBJECT_ARRAY_ARRAYLIKE_H

#include <l0-infra/array/config.h>

#if HAS_CONCEPT
#include <object-array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept {
    template<typename T>
    concept ConstArrayLike = SimpleConstArrayLike<T> &&
    requires(T const& o) {
        { o.GetRange() } -> std::same_as<typename T::SizeType>;
    };
}
#endif

#endif //OBJECT_ARRAY_ARRAYLIKE_H
