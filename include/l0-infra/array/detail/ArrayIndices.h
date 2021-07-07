//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_ARRAYINDICES_H
#define OBJECT_ARRAY_ARRAYINDICES_H

#include <l0-infra/array/holder/ArrayIndicesDataHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>
#include <l0-infra/array/mixin/array_like/RangedArrayLike.h>
#include <l0-infra/array/mixin/array_like/ObjectIndex.h>
#include <l0-infra/array/mixin/detail/___public_mixin_delimiter___.h>
#include <l0-infra/array/mixin/accessor/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/accessor/ByIndexAccessor.h>
#include <l0-infra/array/mixin/count/RangedElemsCount.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/erase/RangedClear.h>
#include <l0-infra/array/mixin/sort/ArraySort.h>
#include <l0-infra/array/mixin/erase/RangedClearExt.h>

namespace detail {
    using ArrayIndicesMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::IndexedContainer,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::RangedClear,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::WithIndexViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::RangedClearExt,
            mixin::ArraySort>;

    template<std::size_t MAX_NUM>
    struct ArrayIndices : ArrayIndicesMixins::Compose<holder::ArrayIndicesDataHolder<MAX_NUM>> {
        using Parent = ArrayIndicesMixins::Compose<holder::ArrayIndicesDataHolder<MAX_NUM>>;
        using Parent::Parent;
        using Parent::IndexBegin;
        using Parent::IndexEnd;
        using Parent::ObjectBegin;
        using Parent::ObjectEnd;
    };
}

#endif //OBJECT_ARRAY_ARRAYINDICES_H
