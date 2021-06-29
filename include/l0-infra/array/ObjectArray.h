//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <l0-infra/array/mixin/SortViewFactory.h>
#include <l0-infra/array/mixin/ArrayEquality.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/ObjectIndex.h>
#include <l0-infra/array/mixin/ReplaceExt.h>
#include <l0-infra/array/mixin/AppendExt.h>
#include <l0-infra/array/mixin/ScopedMinElem.h>
#include <l0-infra/array/mixin/SimpleMinElem.h>
#include <l0-infra/array/mixin/ScopedFindExt.h>
#include <l0-infra/array/mixin/ScopedForEachExt.h>
#include <l0-infra/array/mixin/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/RangedViewFactory.h>
#include <l0-infra/array/mixin/SimpleMutate.h>
#include <l0-infra/array/mixin/EraseExt.h>
#include <l0-infra/array/mixin/ScopedCleanUp.h>
#include <l0-infra/array/mixin/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/RangedArray.h>

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
            mixin::SortViewFactory,
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
