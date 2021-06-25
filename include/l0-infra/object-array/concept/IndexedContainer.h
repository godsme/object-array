//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_INDEXEDCONTAINER_H
#define OBJECT_ARRAY_INDEXEDCONTAINER_H

#include <l0-infra/object-array/config.h>
#if HAS_CONCEPT
#include <concepts>

namespace _concept {
    template<typename T>
    concept ConstIndexedContainer =
    requires(T const& o) {
        { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType const&>;
    };

    template<typename T>
    concept IndexedContainer = ConstIndexedContainer<T> &&
    requires(std::decay_t<T>& o) {
        { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType&>;
    };
}
#endif

#endif //OBJECT_ARRAY_INDEXEDCONTAINER_H
