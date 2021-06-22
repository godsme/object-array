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

template<typename T, std::size_t MAX_NUM, typename Parent = detail::ObjectArray<T, MAX_NUM>>
class ObjectArray : Parent {
    using Holder = typename Parent::Holder;
    using Mixins = typename Parent::Mixins;

public:
    using Parent::Parent;

    using Mixins::Find;
    using Mixins::FindIndex;
    using Parent::Slice;
    using Parent::Scope;
    using Parent::Exclude;
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
