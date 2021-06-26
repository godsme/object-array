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
            mixin::IndexedViewFactory,
            mixin::ArraySortExt>;

    template<typename ARRAY>
    using ArraySortObject = SimpleReadOnlyArrayLike<holder::RefSortObjectHolder<ARRAY>, ArraySortObjectMixins, true>;
}

template<typename ARRAY>
class ArraySortObject : public detail::ArraySortObject<ARRAY> {
    using Parent = detail::ArraySortObject<ARRAY>;
    using typename Parent::Mixins;
    using typename Parent::Holder;

public:
    ArraySortObject(ARRAY& array) : Parent{array} {
        Holder::indices.InitWith(array);
    }

    using Mixins::Sort;
    using Mixins::DescSort;
    using Mixins::PartialSort;
    using Mixins::PartialDescSort;
    using Mixins::StableSort;
    using Mixins::StableDescSort;
};

#endif //OBJECT_ARRAY_ARRAYSORTOBJECT_H
