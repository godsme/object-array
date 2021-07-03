//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_INDEXEDORDEREDARRAY_H
#define OBJECT_ARRAY_INDEXEDORDEREDARRAY_H

#include <l0-infra/array/holder/IndexedOrderedArrayDataHolder.h>
#include <l0-infra/array/mixin/array_like/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>
#include <l0-infra/array/mixin/array_like/ObjectIndex.h>
#include <l0-infra/array/mixin/count/ArrayEquality.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/append/IndexedOrderedAppend.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElem.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElem.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/find/ScopedFindExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/factory/RangedViewFactory.h>
#include <l0-infra/array/mixin/detail/___public_mixin_delimiter___.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/erase/SimpleErase.h>
#include <l0-infra/array/mixin/erase/IndexedOrderedDoErase.h>
#include <l0-infra/array/mixin/erase/IndexedOrderedRangedClear.h>

namespace detail {
    using IndexedOrderedArrayMixins = ::mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::SimpleForEach,
            mixin::ScopedForEach,
            mixin::IndexedOrderedDoErase,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::ArrayEquality,
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::RangedViewFactory,
            mixin::ScopedViewFactory,
            mixin::IndexedViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::IndexedOrderedRangedClear,
            mixin::SimpleErase,
            mixin::IndexedOrderedAppend,
            mixin::AppendExt>;

    template<typename T, std::size_t MAX_NUM, typename COMPARE>
    using IndexedOrderedArray = detail::IndexedOrderedArrayMixins::Compose<holder::IndexedOrderedArrayHolder<T, MAX_NUM, COMPARE>>;
}

template<typename T, std::size_t MAX_NUM, typename COMPARE = std::less<T>>
using IndexedOrderedArray = detail::IndexedOrderedArray<T, MAX_NUM, COMPARE>;

#endif //OBJECT_ARRAY_INDEXEDORDEREDARRAY_H
