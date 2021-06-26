//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_ARRAYINDICES_H
#define OBJECT_ARRAY_ARRAYINDICES_H

#include <l0-infra/array/holder/ArrayIndicesDataHolder.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLikeMixins.h>
#include <l0-infra/array/detail/ContinuousRangedArray.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLike.h>
#include <l0-infra/array/mixin/ArraySortExt.h>
#include <l0-infra/array/mixin/IndexedViewFactory.h>
#include <l0-infra/array/mixin/ArraySort.h>

namespace detail {
    using ArrayIndicesMixins = ContinuousRangedArray
            ::Concat<SimpleReadOnlyArrayLikeMixins>
                    ::Extends<
                        mixin::IndexedViewFactory,
                        mixin::ArraySort,
                        mixin::ArraySortExt>;

    template<std::size_t MAX_NUM>
    using ArrayIndices = SimpleReadOnlyArrayLike<holder::ArrayIndicesDataHolder<MAX_NUM>, ArrayIndicesMixins, true>;
}

template<std::size_t MAX_NUM>
class ArrayIndices : public detail::ArrayIndices<MAX_NUM> {
    using Parent = detail::ArrayIndices<MAX_NUM>;
    using typename Parent::Mixins;
    using typename Parent::Holder;

public:
    using Parent::Parent;
    using Holder::InitWith;
    using Holder::InitWithRange;

    using Mixins::Sort;
    using Mixins::DescSort;
    using Mixins::PartialSort;
    using Mixins::PartialDescSort;
    using Mixins::StableSort;
    using Mixins::StableDescSort;
};

#endif //OBJECT_ARRAY_ARRAYINDICES_H
