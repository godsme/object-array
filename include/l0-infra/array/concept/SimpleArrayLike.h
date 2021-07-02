//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SIMPLEARRAYLIKE_H
#define OBJECT_ARRAY_SIMPLEARRAYLIKE_H

#include <l0-infra/array/detail/config.h>
#if HAS_CONCEPT
#include <concepts>

namespace _concept::detail {
    template<typename T>
    struct SimpleConstArrayLikeChecker : T {
        using T::Elems;
        using T::ConstElemToObject;
        using typename T::ElemType;
        using typename T::ObjectType;
        using typename T::Trait;
    };

    template<typename T>
    concept SimpleConstArrayLike = requires(T const& o, typename T::ElemType const& elem) {
        typename T::Trait;
        { o.Elems() } -> std::same_as<typename T::ElemType const*>;
        { T::ConstElemToObject(elem) } -> std::same_as<typename T::ObjectType const&>;
    };
}

namespace _concept {
    template<typename T>
    concept SimpleConstArrayLike = detail::SimpleConstArrayLike<detail::SimpleConstArrayLikeChecker<T>>;
}

namespace _concept::detail {
    template<typename T>
    struct SimpleArrayLikeChecker : T {
        using T::Elems;
        using T::ElemToObject;
        using typename T::ElemType;
        using typename T::ObjectType;
        using typename T::Trait;
    };

    template<typename T>
    concept NonConstSimpleArrayLike_ = requires(T& o, typename T::ElemType& elem) {
        { o.Elems() } -> std::same_as<typename T::ElemType*>;
        { T::ElemToObject(elem) } -> std::same_as<typename T::ObjectType&>;
    };

    template<typename T>
    concept NonConstSimpleArrayLike = NonConstSimpleArrayLike_<SimpleArrayLikeChecker<std::decay_t<T>>>;
}

namespace _concept {
    template<typename T>
    concept SimpleArrayLike = SimpleConstArrayLike<T> && detail::NonConstSimpleArrayLike<T>;
}

#endif

#endif //OBJECT_ARRAY_SIMPLEARRAYLIKE_H
