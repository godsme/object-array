//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SIMPLEARRAYLIKE_H
#define OBJECT_ARRAY_SIMPLEARRAYLIKE_H

#include <concepts>

namespace _concept {
    template<typename T>
    concept SimpleConstArrayLike = requires(T const& o) {
        { o.Elems() } -> std::same_as<typename T::ElemType const*>;
        { T::ElemToObject(std::declval<typename T::ElemType const&>()) } -> std::same_as<typename T::ObjectType const&>;
    };

    template<typename T>
    concept SimpleArrayLike = SimpleConstArrayLike<T> && requires(std::decay_t<T>& o) {
        { o.Elems() } -> std::same_as<typename std::decay_t<T>::ElemType*>;
        { std::decay_t<T>::ElemToObject(std::declval<typename std::decay_t<T>::ElemType&>()) } -> std::same_as<typename std::decay_t<T>::ObjectType&>;
    };
}

#endif //OBJECT_ARRAY_SIMPLEARRAYLIKE_H
