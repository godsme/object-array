//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <l0-infra/array/detail/ContinuousArrayMixin.h>
#include <l0-infra/array/mixin/SortViewFactory.h>
#include <l0-infra/array/mixin/ArrayEquality.h>
#include <l0-infra/array/mixin/detail/MutableMixin.h>

namespace detail {
    using ObjectArrayMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::SimpleForEach,
            mixin::ScopedForEach,
            mixin::ScopedMinElem,
            mixin::detail::__PublicMixinDelimiter__,
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
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::detail::Mutable<mixin::SimpleMutate>::template Mixin,
            mixin::detail::Mutable<mixin::SimpleMutateExt>::template Mixin,
            mixin::detail::Mutable<mixin::PredBasedMutate>::template Mixin,
            mixin::detail::Mutable<mixin::ScopedCleanUp>::template Mixin,
            mixin::detail::Mutable<mixin::RangedClear>::template Mixin,
            mixin::detail::Mutable<mixin::ArraySort>::template Mixin,
            mixin::detail::Mutable<mixin::ArraySortExt>::template Mixin,
            mixin::RangedViewFactory,
            mixin::ScopedViewFactory,
            mixin::IndexedViewFactory,
            mixin::SortViewFactory>;

    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = detail::ObjectArrayMixins::Compose<holder::ObjectArrayDataHolder<T, MAX_NUM>>;
}

template<typename T, std::size_t MAX_NUM>
using ObjectArray = detail::ObjectArray<T, MAX_NUM>;

#endif //OBJECT_ARRAY_OBJECTARRAY_H
