//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SIMPLEARRAYLIKE_H
#define OBJECT_ARRAY_SIMPLEARRAYLIKE_H

#include <l0-infra/array/detail/config.h>
#if HAS_CONCEPT
#include <concepts>

namespace _concept {
    namespace detail {
        template<typename T>
        struct SimpleConstArrayLikeChecker : T {
            using T::Elems;
            using T::ConstElemToObject;
            using typename T::ElemType;
            using typename T::ObjectType;
            using typename T::Trait;
        };
        template<typename T>
        concept SimpleConstArrayLike_ = requires(T const& o) {
            typename T::Trait;
            { o.Elems() } -> std::same_as<typename T::ElemType const*>;
            { T::ConstElemToObject(std::declval<typename T::ElemType const&>()) } -> std::same_as<typename T::ObjectType const&>;
        };
    }

    template<typename T>
    concept SimpleConstArrayLike = detail::SimpleConstArrayLike_<detail::SimpleConstArrayLikeChecker<T>>;

    namespace detail {
        template<typename T>
        struct SimpleArrayLikeChecker : T {
            using T::Elems;
            using T::ElemToObject;
            using typename T::ElemType;
            using typename T::ObjectType;
            using typename T::Trait;
        };

        template<typename T>
        concept NonConstSimpleArrayLike_ =  requires(T& o) {
            { o.Elems() } -> std::same_as<typename T::ElemType*>;
            { T::ElemToObject(std::declval<typename T::ElemType&>()) } -> std::same_as<typename T::ObjectType&>;
        };

        template<typename T>
        concept NonConstSimpleArrayLike = NonConstSimpleArrayLike_<SimpleArrayLikeChecker<std::decay_t<T>>>;
    }

    template<typename T>
    concept SimpleArrayLike = SimpleConstArrayLike<T> && detail::NonConstSimpleArrayLike<T>;
}

#endif

#endif //OBJECT_ARRAY_SIMPLEARRAYLIKE_H
