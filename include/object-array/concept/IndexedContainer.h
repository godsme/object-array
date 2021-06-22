//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_INDEXEDCONTAINER_H
#define OBJECT_ARRAY_INDEXEDCONTAINER_H

#include <concepts>

namespace _concept {
    template<typename T>
    concept IndexedContainer = requires(T const& o) {
        typename T::SizeType;
        typename T::ObjectType;
        { o.GetObj(std::declval<typename T::SizeType>()) } -> std::same_as<typename T::ObjectType const&>;
    };
}

#endif //OBJECT_ARRAY_INDEXEDCONTAINER_H
