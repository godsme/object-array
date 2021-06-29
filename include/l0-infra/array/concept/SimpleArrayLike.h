//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SIMPLEARRAYLIKE_H
#define OBJECT_ARRAY_SIMPLEARRAYLIKE_H

#include <l0-infra/array/detail/config.h>
#if HAS_CONCEPT
#include <concepts>

namespace _concept {
    template<typename T>
    struct SimpleConstArrayLikeChecker : T {
        using T::Elems;
        using T::ConstElemToObject;
        using typename T::ElemType;
        using typename T::ObjectType;
        using typename T::Trait;
    };

    template<typename T>
    concept SimpleConstArrayLike = requires(SimpleConstArrayLikeChecker<T> const& o) {
        typename SimpleConstArrayLikeChecker<T>::Trait;
        { o.Elems() } -> std::same_as<typename SimpleConstArrayLikeChecker<T>::ElemType const*>;
        { SimpleConstArrayLikeChecker<T>::ConstElemToObject(std::declval<typename SimpleConstArrayLikeChecker<T>::ElemType const&>()) } -> std::same_as<typename T::ObjectType const&>;
    };

    template<typename T>
    struct SimpleArrayLikeChecker : T {
        using T::Elems;
        using T::ElemToObject;
        using typename T::ElemType;
        using typename T::ObjectType;
        using typename T::Trait;
    };

    template<typename T>
    concept SimpleArrayLike = SimpleConstArrayLike<T> && requires(SimpleArrayLikeChecker<std::decay_t<T>>& o) {
        { o.Elems() } -> std::same_as<typename SimpleArrayLikeChecker<std::decay_t<T>>::ElemType*>;
        { SimpleArrayLikeChecker<std::decay_t<T>>::ElemToObject(std::declval<typename SimpleArrayLikeChecker<std::decay_t<T>>::ElemType&>()) } -> std::same_as<typename SimpleArrayLikeChecker<std::decay_t<T>>::ObjectType&>;
    };
}
#endif

#endif //OBJECT_ARRAY_SIMPLEARRAYLIKE_H
