//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDARRAYLIKE_H
#define OBJECT_ARRAY_SCOPEDARRAYLIKE_H

#include <object-array/concept/RangedArrayLike.h>

namespace _concept {
    template<typename T>
    concept ScopedArrayLike = requires(T const& o) {
        typename T::BitMap;
        { o.GetScope() } -> std::same_as<typename T::BitMap>;
    };

    template<typename T>
    concept ScopedRangedArrayLike = ScopedArrayLike<T> && RangedArrayLike<T>;

    template<typename T>
    concept SimpleScopedRangedArrayLike = ScopedArrayLike<T> && SimpleRangedArrayLike<T>;
}

#endif //OBJECT_ARRAY_SCOPEDARRAYLIKE_H
