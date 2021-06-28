//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <l0-infra/array/detail/ContinuousArrayMixin.h>
#include <l0-infra/array/detail/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/SortViewFactory.h>

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
            mixin::detail::PublicMixinSplitter,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::SimpleMutate,
            mixin::SimpleMutateExt,
            mixin::PredBasedMutate,
            mixin::ScopedCleanUp,
            mixin::RangedClear,
            mixin::RangedViewFactory,
            mixin::ScopedViewFactory,
            mixin::IndexedViewFactory,
            mixin::SortViewFactory,
            mixin::ArraySort,
            mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = holder::ObjectArrayDataHolder<T, MAX_NUM, detail::ObjectArrayMixins>;
}

template<typename T, std::size_t MAX_NUM>
struct ObjectArray : detail::ObjectArray<T, MAX_NUM> {
    using Parent = detail::ObjectArray<T, MAX_NUM>;
    using Parent::Parent;
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
