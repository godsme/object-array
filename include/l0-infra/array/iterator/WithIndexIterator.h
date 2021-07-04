//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_WITHINDEXITERATOR_H
#define OBJECT_ARRAY_WITHINDEXITERATOR_H

#include <l0-infra/array/iterator/Iterator.h>
#include <l0-infra/array/iterator/detail/IndexedIterator.h>

namespace iterator {
    template<typename T, typename SIZE_TYPE>
    struct WithIndexIterator : detail::IndexedIterator<T, SIZE_TYPE> {
        using Parent = detail::IndexedIterator<T, SIZE_TYPE>;
        using Parent::Parent;
        auto operator++() -> WithIndexIterator& {
            Parent::StepForward();
            return *this;
        }
    };
}

#endif //OBJECT_ARRAY_WITHINDEXITERATOR_H
