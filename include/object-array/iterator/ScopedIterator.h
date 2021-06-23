//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_SCOPEDITERATOR_H
#define OBJECT_ARRAY_SCOPEDITERATOR_H

#include <object-array/iterator/detail/ScopedIterator.h>
#include <object-array/iterator/detail/SimpleIterator.h>

namespace iterator {
    template<typename T, typename BIT_MAP>
    using ScopedIterator = detail::ScopedIterator<detail::SimpleIterator<T>, BIT_MAP>;
}

#endif //OBJECT_ARRAY_SCOPEDITERATOR_H
