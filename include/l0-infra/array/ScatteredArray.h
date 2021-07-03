//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <l0-infra/array/holder/ScatteredArrayDataHolder.h>
#include <l0-infra/array/mixin/find/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/iterable/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>
#include <l0-infra/array/mixin/array_like/RangedArrayLike.h>
#include <l0-infra/array/mixin/accessor/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/accessor/ByIndexAccessor.h>
#include <l0-infra/array/mixin/accessor/ScopedByIndexAccessor.h>
#include <l0-infra/array/mixin/array_like/ArrayElemVisit.h>
#include <l0-infra/array/mixin/foreach/ScopedSimpleForEach.h>
#include <l0-infra/array/mixin/foreach/SimpleForEachExt.h>
#include <l0-infra/array/mixin/count/FullScopedElemCount.h>
#include <l0-infra/array/mixin/minmax/ScopedSimpleMinElem.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/factory/IndexedScopedViewFactory.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/erase/ScopedCleanUp.h>
#include <l0-infra/array/mixin/factory/ScopedSortViewFactory.h>
#include <l0-infra/array/mixin/sort/ScopedSort.h>
#include <l0-infra/array/mixin/array_like/ScopedRangedArray.h>
#include <l0-infra/array/mixin/count/ArrayEquality.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/array_like/ObjectIndex.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/erase/ScatteredClear.h>

namespace detail {
    using ScatteredArrayMixins = mixin::Mixins<
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ScopedRangedArray,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::ScopedSimpleFind,
            mixin::ScopedForEach,
            mixin::ScopedMinElem,
            mixin::ScopedSimpleForEach,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::FullScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::SimpleFindExt,
            mixin::ArrayEquality,
            mixin::SimpleForEachExt,
            mixin::ScopedSimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSortViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::ReplaceExt,
            mixin::AppendExt,
            mixin::EraseExt,
            mixin::ScatteredClear,
            mixin::ScopedCleanUp,
            mixin::ScopedSort,
            mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM>
    using ScatteredArray = detail::ScatteredArrayMixins::Compose<holder::ScatteredArrayHolder<T, MAX_NUM>>;
}

template<typename T, std::size_t MAX_NUM>
using ScatteredArray = detail::ScatteredArray<T, MAX_NUM>;

#endif //OBJECT_ARRAY_SCATTEREDARRAY_H
