//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERATOR_H
#define OBJECT_ARRAY_ITERATOR_H

#include <object-array/iterator/detail/SimpleIterator.h>

namespace iterator {
    template<typename T>
    struct Iterator : detail::SimpleIterator<T> {
        using Parent = detail::SimpleIterator<T>;
        using Parent::Parent;

        auto operator++() -> Iterator& {
            Parent::Forward();
            return *this;
        }
    };
}

#endif //OBJECT_ARRAY_ITERATOR_H
