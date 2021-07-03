//
// Created by Darwin Yuan on 2021/7/2.
//

#ifndef OBJECT_ARRAY_ORDEREDARRAY_H
#define OBJECT_ARRAY_ORDEREDARRAY_H

#include <l0-infra/array/holder/OrderedArrayDataHolder.h>
#include <l0-infra/array/mixin/array_like/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>
#include <l0-infra/array/mixin/array_like/ObjectIndex.h>
#include <l0-infra/array/mixin/count/ArrayEquality.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/append/OrderedAppend.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElem.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElem.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/find/ScopedFindExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/factory/RangedViewFactory.h>
#include <l0-infra/array/mixin/append/SimpleAppend.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/erase/ScopedCleanUp.h>
#include <l0-infra/array/mixin/detail/___public_mixin_delimiter___.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/erase/SimpleErase.h>
#include <l0-infra/array/mixin/erase/ContiguousDoErase.h>
#include <l0-infra/array/mixin/replace/SimpleReplace.h>
#include <l0-infra/array/mixin/replace/OrderedReplace.h>

namespace detail {
    using OrderedArrayMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::SimpleForEach,
            mixin::ScopedForEach,
            mixin::ContiguousDoErase,
            mixin::OrderedReplace,
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
            mixin::SimpleErase,
            mixin::OrderedAppend,
            mixin::AppendExt,
            mixin::EraseExt,
            mixin::SimpleReplace,
            mixin::ScopedCleanUp,
            mixin::RangedClear>;

    template<typename T, std::size_t MAX_NUM, typename COMPARE>
    using OrderedArray = detail::OrderedArrayMixins::Compose<holder::OrderedArrayHolder<T, MAX_NUM, COMPARE>>;
}

template<typename T, std::size_t MAX_NUM, typename COMPARE = std::less<T>>
using OrderedArray = detail::OrderedArray<T, MAX_NUM, COMPARE>;

#endif //OBJECT_ARRAY_ORDEREDARRAY_H
