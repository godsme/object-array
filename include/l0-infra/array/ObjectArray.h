//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <l0-infra/array/mixin/factory/SortViewFactory.h>
#include <l0-infra/array/mixin/count/ArrayEquality.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/array_like/ObjectIndex.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElem.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElem.h>
#include <l0-infra/array/mixin/find/ScopedFindExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/factory/RangedViewFactory.h>
#include <l0-infra/array/mixin/append/SimpleAppend.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/erase/ScopedCleanUp.h>
#include <l0-infra/array/mixin/array_like/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>
#include <l0-infra/array/mixin/erase/ContiguousDoErase.h>
#include <l0-infra/array/mixin/erase/SimpleErase.h>
#include <l0-infra/array/mixin/replace/SimpleReplace.h>
#include <l0-infra/array/mixin/replace/SimpleDoReplace.h>
#include <l0-infra/array/mixin/append/SimpleDoAppend.h>
#include <l0-infra/array/mixin/detail/___ranged_array_tag___.h>
#include <l0-infra/array/mixin/erase/RangedClearExt.h>

namespace detail {
    using ObjectArrayMixins = ::mixin::Mixins<
        mixin::ContinuousArrayLike,
        mixin::IndexedContainer,
        mixin::RangedArray,
        mixin::RangedArrayLike,
        mixin::ObjectIndex,
        mixin::ArrayElemVisit,
        mixin::SimpleDoAppend,
        mixin::SimpleDoReplace,
        mixin::RangedClear,
        mixin::___ranged_array_tag___,
        mixin::ContiguousDoErase,
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
        mixin::WithIndexViewFactory,
        mixin::SortViewFactory,
        mixin::___mutable_mixin_delimiter___,
        mixin::SimpleErase,
        mixin::SimpleAppend,
        mixin::SimpleReplace,
        mixin::ReplaceExt,
        mixin::AppendExt,
        mixin::EraseExt,
        mixin::ScopedCleanUp,
        mixin::RangedClearExt,
        mixin::ArraySort,
        mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = detail::ObjectArrayMixins::Compose<holder::ObjectArrayDataHolder<T, MAX_NUM>>;
}

template<typename T, std::size_t MAX_NUM>
using ObjectArray = detail::ObjectArray<T, MAX_NUM>;

#endif //OBJECT_ARRAY_OBJECTARRAY_H
