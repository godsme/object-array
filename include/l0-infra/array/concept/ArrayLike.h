//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_ARRAYLIKE_H
#define OBJECT_ARRAY_ARRAYLIKE_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept {
    template<typename T>
    struct ConstArrayLikeChecker : T {
        using T::GetRange;
        using typename T::SizeType;
    };

    template<typename T>
    concept ConstArrayLike = SimpleConstArrayLike<T> &&
    requires(ConstArrayLikeChecker<T> const& o) {
        { o.GetRange() } -> std::same_as<typename ConstArrayLikeChecker<T>::SizeType>;
    };
}

#endif

#endif //OBJECT_ARRAY_ARRAYLIKE_H
