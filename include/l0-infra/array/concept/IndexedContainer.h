//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_INDEXEDCONTAINER_H
#define OBJECT_ARRAY_INDEXEDCONTAINER_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT

#include <concepts>

namespace _concept {

    namespace detail {
        template<typename T>
        struct ConstIndexedContainerChecker : T {
            using T::GetObj;
            using typename T::SizeType;
            using typename T::ObjectType;
        };

        template<typename T>
        concept ConstIndexedContainer_ = requires(T const& o) {
            { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType const&>;
        };
    }

    template<typename T>
    concept ConstIndexedContainer = detail::ConstIndexedContainer_<detail::ConstIndexedContainerChecker<T>>;

    namespace detail {
        template<typename T>
        struct IndexedContainerChecker : T {
            using T::GetObj;
            using typename T::SizeType;
            using typename T::ObjectType;
        };

        template<typename T>
        concept IndexedContainer_ =  requires(T& o) {
            { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType&>;
        };

        template<typename T>
        concept IndexedContainer = detail::IndexedContainer_<detail::IndexedContainerChecker<std::decay_t<T>>>;
    }

    template<typename T>
    concept IndexedContainer = ConstIndexedContainer<T> && detail::IndexedContainer<T>;
}

#endif

#endif //OBJECT_ARRAY_INDEXEDCONTAINER_H
