//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_RANGEDARRAYLIKE_H

#include <type_traits>
#include <optional>
#include <concepts>

namespace _concept {
    template<typename T>
    concept RangedArrayLike = requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        typename T::ElemType;
        { o.IndexBegin() } -> std::same_as<typename T::SizeType>;
        { o.IndexEnd() } -> std::same_as<typename T::SizeType>;
        { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType const&>;
//        { o.Elems() } -> std::same_as<typename T::ElemType const*>;
//        { const_cast<T&>(o).Elems() } -> std::same_as<typename T::ElemType*>;
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAYLIKE_H
