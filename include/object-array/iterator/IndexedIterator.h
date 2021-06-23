//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDITERATOR_H
#define OBJECT_ARRAY_INDEXEDITERATOR_H

#include <object-array/iterator/Iterator.h>
#include <object-array/iterator/detail/IndexedIterator.h>

namespace iterator {
    template<typename T, typename SIZE_TYPE>
    struct IndexedIterator : detail::IndexedIterator<T, SIZE_TYPE> {
        using Parent = detail::IndexedIterator<T, SIZE_TYPE>;
        using Parent::Parent;
        auto operator++() -> IndexedIterator& {
            Parent::Forward();
            return *this;
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDITERATOR_H
