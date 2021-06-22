//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SIMPLEARRAYLIKE_H
#define OBJECT_ARRAY_SIMPLEARRAYLIKE_H

#include <concepts>

namespace _concept {
    template<typename T>
    concept SimpleConstArrayLike = requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        typename T::ElemType;
        { o.Elems() } -> std::same_as<typename T::ElemType const*>;
        { T::ElemToObject(std::declval<typename T::ElemType const&>()) } -> std::same_as<typename T::ObjectType const&>;
    };
}

#endif //OBJECT_ARRAY_SIMPLEARRAYLIKE_H
