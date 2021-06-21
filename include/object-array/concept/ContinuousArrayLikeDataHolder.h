//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H

#include <object-array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept {
    template<typename T>
    concept ContinuousArrayLikeDataHolder = SimpleConstArrayLike<T> && requires(T const& o) {
        { o.num } -> std::same_as<typename T::SizeType>;
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H
