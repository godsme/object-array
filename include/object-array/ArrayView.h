//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYVIEW_H
#define OBJECT_ARRAY_ARRAYVIEW_H

#include <object-array/holder/ArrayViewDataHolder.h>
#include <object-array/detail/ContinuousArrayMixin.h>
#include <object-array/detail/ArrayComposer.h>

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = T>
class ArrayView : detail::ArrayComposer<holder::ArrayViewDataHolder<T, SIZE_TYPE, MAX_NUM, ELEM>, detail::ContinuousArrayMixin> {
    using Parent = detail::ArrayComposer<holder::ArrayViewDataHolder<T, SIZE_TYPE, MAX_NUM, ELEM>, detail::ContinuousArrayMixin>;
    using Holder = typename Parent::Holder;
public:
    using Parent::Parent;

    using Parent::Find;
    using Parent::FindIndex;
    using Parent::Slice;
    using Parent::Scope;
    using Parent::Exclude;
    using Parent::WithIndex;
    using Parent::begin;
    using Parent::end;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ArrayView(T (&)[MAX_NUM], SIZE_TYPE& size) -> ArrayView<T, SIZE_TYPE, MAX_NUM>;

#endif //OBJECT_ARRAY_ARRAYVIEW_H
