//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <l0-infra/array/holder/ScatteredArrayDataHolder.h>
#include <l0-infra/array/detail/ReadOnlyArrayLike.h>
#include <l0-infra/array/mixin/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/SimpleFindExt.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/RangedArray.h>
#include <l0-infra/array/mixin/RangedArrayLike.h>
#include <l0-infra/array/mixin/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/ByIndexAccessor.h>
#include <l0-infra/array/mixin/ScopedByIndexAccessor.h>
#include <l0-infra/array/mixin/ArrayElemVisit.h>
#include <l0-infra/array/mixin/ScopedSimpleForEach.h>
#include <l0-infra/array/mixin/SimpleForEachExt.h>
#include <l0-infra/array/mixin/FullScopedElemCount.h>
#include <l0-infra/array/mixin/ScopedSimpleMinElem.h>
#include <l0-infra/array/mixin/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/IndexedScopedViewFactory.h>
#include <l0-infra/array/mixin/SimpleMutateExt.h>
#include <l0-infra/array/mixin/PredBasedMutate.h>
#include <l0-infra/array/mixin/ScopedCleanUp.h>
#include <l0-infra/array/mixin/ScopedSortViewFactory.h>
#include <l0-infra/array/mixin/ScopedSort.h>
#include <l0-infra/array/mixin/ScopedRangedArray.h>
#include <l0-infra/array/mixin/ArrayEquality.h>

namespace detail {
    using ScatteredArrayMixins = mixin::Mixins<
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ScopedRangedArray,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::ScopedSimpleFind,
            mixin::ScopedForEach,
            mixin::ScopedMinElem,
            mixin::ScopedSimpleForEach,
            mixin::detail::PublicMixinSplitter,
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
            mixin::SimpleMutateExt,
            mixin::PredBasedMutate,
            mixin::ScopedCleanUp,
            mixin::ScopedSortViewFactory,
            mixin::ScopedSort,
            mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM>
    using ScatteredArray = detail::ScatteredArrayMixins::Compose<holder::ScatteredArrayHolder<T, MAX_NUM>>;
}

template<typename T, std::size_t MAX_NUM>
using ScatteredArray = detail::ScatteredArray<T, MAX_NUM>;

#endif //OBJECT_ARRAY_SCATTEREDARRAY_H
