//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_INDEXEDCONTAINER_H
#define OBJECT_ARRAY_INDEXEDCONTAINER_H

#include <l0-infra/array/detail/config.h>
#if HAS_CONCEPT
#include <concepts>

namespace _concept {

    template<typename T>
    struct ConstIndexedContainerChecker : T {
        using T::GetObj;
        using typename T::SizeType;
        using typename T::ObjectType;
    };

    template<typename T>
    concept ConstIndexedContainer =
    requires(ConstIndexedContainerChecker<T> const& o) {
        { o.GetObj(std::declval<typename ConstIndexedContainerChecker<T>::SizeType>()) } -> std::same_as<typename ConstIndexedContainerChecker<T>::ObjectType const&>;
    };

    template<typename T>
    struct IndexedContainerChecker : T {
        using T::GetObj;
        using typename T::SizeType;
        using typename T::ObjectType;
    };

    template<typename T>
    concept IndexedContainer = ConstIndexedContainer<T> &&
    requires(IndexedContainerChecker<std::decay_t<T>>& o) {
        { o.GetObj(std::declval<typename IndexedContainerChecker<std::decay_t<T>>::SizeType>()) } -> std::same_as<typename IndexedContainerChecker<std::decay_t<T>>::ObjectType&>;
    };
}

#endif

#endif //OBJECT_ARRAY_INDEXEDCONTAINER_H
