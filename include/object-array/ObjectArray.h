//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <object-array/holder/ObjectArrayDataHolder.h>
#include <object-array/detail/ContinuousArrayMixin.h>
#include <object-array/detail/ArrayComposer.h>

template<typename T, std::size_t MAX_NUM>
class ObjectArray : detail::ArrayComposer<holder::ObjectArrayDataHolder<T, MAX_NUM>, detail::ContinuousArrayMixin> {
    using Parent = detail::ArrayComposer<holder::ObjectArrayDataHolder<T, MAX_NUM>, detail::ContinuousArrayMixin>;

    using Holder = typename Parent::Holder;
    using Mixins = typename Parent::Mixins;

public:
    using Parent::Parent;

    using Mixins::Find;
    using Mixins::FindIndex;
    using Parent::Slice;
    using Parent::Scope;
    using Parent::Exclude;
    using Parent::WithIndex;
    using Parent::begin;
    using Parent::end;
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
