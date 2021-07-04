//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_WITHINDEXSCOPEDITERATOR_H
#define OBJECT_ARRAY_WITHINDEXSCOPEDITERATOR_H

#include <l0-infra/array/iterator/detail/ScopedIterator.h>
#include <l0-infra/array/iterator/detail/WithIndexIterator.h>

namespace iterator {
    template<typename T, typename BIT_MAP, typename SIZE_TYPE>
    using IndexedScopedIterator = detail::ScopedIterator<detail::WithIndexIterator<T, SIZE_TYPE>, BIT_MAP>;
}

#endif //OBJECT_ARRAY_WITHINDEXSCOPEDITERATOR_H