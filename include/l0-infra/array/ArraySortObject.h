//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_ARRAYSORTOBJECT_H
#define OBJECT_ARRAY_ARRAYSORTOBJECT_H

#include <l0-infra/array/holder/SortObjectDataHolder.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLike.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLikeMixins.h>

namespace detail {
    using ArraySortObjectMixins = SimpleReadOnlyArrayLikeMixins::Extends<
            mixin::IndexedViewFactory>;

    template<typename ARRAY>
    using ArraySortObject = SimpleReadOnlyArrayLike<holder::RefSortObjectHolder<ARRAY>, ArraySortObjectMixins, true>;
}

template<typename ARRAY>
struct ArraySortObject : detail::ArraySortObject<ARRAY> {
    using Parent = detail::ArraySortObject<ARRAY>;
    using Parent::Parent;
};

#endif //OBJECT_ARRAY_ARRAYSORTOBJECT_H
