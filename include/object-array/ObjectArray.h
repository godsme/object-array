//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <object-array/holder/ObjectArrayDataHolder.h>
#include <object-array/detail/ContinuousArrayMixin.h>
#include <object-array/detail/ArrayComposer.h>

namespace detail {
    using ObjectArrayMixins =
            detail::ContinuousArrayMixin::Extends<
                mixin::RangedViewFactory,
                mixin::ScopedViewFactory,
                mixin::IndexedViewFactory>;

    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = detail::ArrayComposer<holder::ObjectArrayDataHolder<T, MAX_NUM>, ObjectArrayMixins>;
}

template<typename T, std::size_t MAX_NUM>
class ObjectArray : detail::ObjectArray<T, MAX_NUM> {
    using Parent = detail::ObjectArray<T, MAX_NUM>;

    using Holder = typename Parent::Holder;
    using Mixins = typename Parent::Mixins;

public:
    using Parent::Parent;

    using Parent::begin;
    using Parent::end;

    using Mixins::Find;
    using Mixins::FindIndex;
    using Mixins::Exists;

    using Parent::Slice;
    using Parent::From;
    using Parent::Until;

    using Parent::Scope;
    using Parent::Exclude;
    using Parent::WithIndex;
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
