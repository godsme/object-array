//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <l0-infra/array/holder/ScatteredArrayDataHolder.h>
#include <l0-infra/array/mixin/scoped/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/simple/SimpleFindExt.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/scoped/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/ranged/RangedArray.h>
#include <l0-infra/array/mixin/ranged/RangedArrayLike.h>
#include <l0-infra/array/mixin/indexed/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/simple/ByIndexAccessor.h>
#include <l0-infra/array/mixin/scoped/ScopedByIndexAccessor.h>
#include <l0-infra/array/mixin/simple/ArrayElemVisit.h>
#include <l0-infra/array/mixin/scoped/ScopedSimpleForEach.h>
#include <l0-infra/array/mixin/simple/SimpleForEachExt.h>
#include <l0-infra/array/mixin/scoped/FullScopedElemCount.h>
#include <l0-infra/array/mixin/scoped/ScopedSimpleMinElem.h>
#include <l0-infra/array/mixin/simple/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/indexed/IndexedScopedViewFactory.h>
#include <l0-infra/array/mixin/mutable/EraseExt.h>
#include <l0-infra/array/mixin/scoped/ScopedCleanUp.h>
#include <l0-infra/array/mixin/scoped/ScopedSortViewFactory.h>
#include <l0-infra/array/mixin/scoped/ScopedSort.h>
#include <l0-infra/array/mixin/scoped/ScopedRangedArray.h>
#include <l0-infra/array/mixin/simple/ArrayEquality.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/indexed/ObjectIndex.h>
#include <l0-infra/array/mixin/mutable/ReplaceExt.h>
#include <l0-infra/array/mixin/mutable/AppendExt.h>

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
            mixin::ScopedCleanUp,
            mixin::ScopedSort,
            mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM>
    using ScatteredArray = detail::ScatteredArrayMixins::Compose<holder::ScatteredArrayHolder<T, MAX_NUM>>;
}

template<typename T, std::size_t MAX_NUM>
using ScatteredArray = detail::ScatteredArray<T, MAX_NUM>;

#endif //OBJECT_ARRAY_SCATTEREDARRAY_H
