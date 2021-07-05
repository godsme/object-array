//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAY_H
#define OBJECT_ARRAY_DYNAMICARRAY_H

#include <l0-infra/array/holder/DynamicArrayDataHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>
#include <l0-infra/array/mixin/array_like/DynamicObjectIndex.h>
#include <l0-infra/array/mixin/erase/SimpleRangedClear.h>
#include <l0-infra/array/mixin/sort/DynamicArraySort.h>

namespace detail {
    using DynamicArrayMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::___ranged_array_tag___,
            mixin::DynamicObjectIndex,
            mixin::ArrayElemVisit,
            mixin::SimpleForEach,
            mixin::SimpleRangedClear,
            mixin::ScopedFind,
            mixin::ScopedForEach,
            mixin::ScopedMinElem,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableIndexBasedArray,
            mixin::SimpleForEachExt,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ArrayEquality,
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::ScopedMinElemExt,
            mixin::RangedViewFactory,
            mixin::ScopedViewFactory,
            mixin::WithIndexViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleAppend,
            mixin::AppendExt,
            mixin::SimpleErase,
            mixin::EraseExt,
            mixin::RangedClearExt,
            mixin::DynamicArraySort,
            mixin::ArraySortExt>;
}

template<typename ALLOCATOR, std::size_t MAX_NUM>
using DynamicArray = detail::DynamicArrayMixins::Compose<holder::DynamicArrayDataHolder<ALLOCATOR, MAX_NUM>>;

#endif //OBJECT_ARRAY_DYNAMICARRAY_H
