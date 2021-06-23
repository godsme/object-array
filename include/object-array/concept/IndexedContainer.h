//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_INDEXEDCONTAINER_H
#define OBJECT_ARRAY_INDEXEDCONTAINER_H

#include <concepts>

namespace _concept {
    template<typename T>
    concept ConstIndexedContainer = requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType const&>;
    };

    template<typename T>
    concept IndexedContainer = ConstIndexedContainer<T> && requires(std::decay_t<T>& o) {
        typename T::SizeType;
        typename T::ObjectType;
        { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType&>;
    };
}

#endif //OBJECT_ARRAY_INDEXEDCONTAINER_H
