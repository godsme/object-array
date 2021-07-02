//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <l0-infra/array/mixin/sort/SortViewFactory.h>
#include <l0-infra/array/mixin/simple/ArrayEquality.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/indexed/ObjectIndex.h>
#include <l0-infra/array/mixin/mutable/ReplaceExt.h>
#include <l0-infra/array/mixin/mutable/AppendExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElem.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElem.h>
#include <l0-infra/array/mixin/find/ScopedFindExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/ranged/RangedViewFactory.h>
#include <l0-infra/array/mixin/mutable/SimpleMutate.h>
#include <l0-infra/array/mixin/mutable/EraseExt.h>
#include <l0-infra/array/mixin/mutable/ScopedCleanUp.h>
#include <l0-infra/array/mixin/simple/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/ranged/RangedArray.h>

namespace detail {

    using ObjectArrayMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::SimpleForEach,
            mixin::ScopedForEach,
            mixin::ScopedMinElem,
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
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::RangedViewFactory,
            mixin::ScopedViewFactory,
            mixin::IndexedViewFactory,
            mixin::SortViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleMutate,
            mixin::ReplaceExt,
            mixin::AppendExt,
            mixin::EraseExt,
            mixin::ScopedCleanUp,
            mixin::RangedClear,
            mixin::ArraySort,
            mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = detail::ObjectArrayMixins::Compose<holder::ObjectArrayDataHolder<T, MAX_NUM>>;
}

template<typename T, std::size_t MAX_NUM>
using ObjectArray = detail::ObjectArray<T, MAX_NUM>;

#endif //OBJECT_ARRAY_OBJECTARRAY_H
