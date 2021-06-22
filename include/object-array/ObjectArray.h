//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <object-array/holder/ObjectArrayDataHolder.h>
#include <object-array/detail/ContinuousArrayMixin.h>

namespace detail {
    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = ContinuousArrayMixin<holder::ObjectArrayDataHolder<T, MAX_NUM>>;
}

template<typename T, std::size_t MAX_NUM>
struct ObjectArray : detail::ObjectArray<T, MAX_NUM> {
    using Parent = detail::ObjectArray<T, MAX_NUM>;
    using Parent::Parent;
    using Holder = typename Parent::Holder;

    using Holder::Elems;
    using Holder::Num;
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
