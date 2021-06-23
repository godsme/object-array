//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYVIEW_H
#define OBJECT_ARRAY_ARRAYVIEW_H

#include <object-array/holder/ArrayViewDataHolder.h>
#include <object-array/detail/ContinuousArrayMixin.h>

namespace detail {
    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM>
    using ArrayView = ContinuousArrayMixin<
            holder::ArrayViewDataHolder<T, SIZE_TYPE, MAX_NUM, ELEM>>;
}

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = T, typename Parent = detail::ArrayView<T, SIZE_TYPE, MAX_NUM, ELEM>>
class ArrayView : Parent {
    using Holder = typename Parent::Holder;
public:
    using Parent::Parent;

    using Parent::Find;
    using Parent::FindIndex;
    using Parent::Slice;
    using Parent::Scope;
    using Parent::Exclude;
    using Parent::WithIndex;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ArrayView(T (&)[MAX_NUM], SIZE_TYPE& size) -> ArrayView<T, SIZE_TYPE, MAX_NUM>;

#endif //OBJECT_ARRAY_ARRAYVIEW_H
