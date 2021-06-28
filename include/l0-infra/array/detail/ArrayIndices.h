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
#include <l0-infra/array/mixin/RangedClear.h>

namespace detail {
    using ArrayIndicesMixins = ContinuousRangedArray
    ::Concat<SimpleReadOnlyArrayLikeMixins>
    ::Extends<mixin::RangedClear,
            mixin::IndexedViewFactory,
            mixin::ArraySort,
            mixin::ArraySortExt>;

    template<std::size_t MAX_NUM>
    using ArrayIndices = holder::ArrayIndicesDataHolder<MAX_NUM, ArrayIndicesMixins>;
}

#endif //OBJECT_ARRAY_ARRAYINDICES_H
