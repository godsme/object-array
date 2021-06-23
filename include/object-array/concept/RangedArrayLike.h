//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_RANGEDARRAYLIKE_H

#include <object-array/concept/IndexedContainer.h>
#include <concepts>

namespace _concept {
    template<typename T>
    concept SimpleRangedArrayLike = IndexedContainer<T> &&
    requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        { o.IndexBegin() } -> std::same_as<typename T::SizeType>;
        { o.IndexEnd() } -> std::same_as<typename T::SizeType>;
    };

    template<typename T>
    concept ConstRangedArrayLike = SimpleRangedArrayLike<T> &&
    requires(T const& o) {
        { o.ObjectBegin() } -> std::same_as<typename T::ObjectType const*>;
        { o.ObjectEnd() } -> std::same_as<typename T::ObjectType const*>;
    };

    template<typename T>
    concept RangedArrayLike = ConstRangedArrayLike<T> &&
    requires(std::decay_t<T>& o) {
       { o.ObjectBegin() } -> std::same_as<typename T::ObjectType*>;
       { o.ObjectEnd() } -> std::same_as<typename T::ObjectType*>;
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAYLIKE_H
