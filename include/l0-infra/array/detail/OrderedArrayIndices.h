//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_ORDEREDARRAYINDICES_H
#define OBJECT_ARRAY_ORDEREDARRAYINDICES_H

#include <l0-infra/array/holder/OrderedArrayIndicesDataHolder.h>
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
#include <l0-infra/array/mixin/erase/ContiguousDoErase.h>
#include <l0-infra/array/mixin/erase/SimpleErase.h>
#include <l0-infra/array/mixin/append/OrderedDoAppend.h>
#include <l0-infra/array/mixin/replace/OrderedDoReplace.h>
#include <l0-infra/array/mixin/find/NonScopedSimpleFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>

namespace detail {
    using OrderedArrayIndicesMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::IndexedContainer,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ContiguousDoErase,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleErase,
            mixin::RangedClear,
            mixin::OrderedDoAppend,
            mixin::OrderedDoReplace>;

    template<std::size_t MAX_NUM>
    struct OrderedArrayIndices : OrderedArrayIndicesMixins::Compose<holder::OrderedArrayIndicesDataHolder<MAX_NUM>> {
        using Parent = OrderedArrayIndicesMixins::Compose<holder::OrderedArrayIndicesDataHolder<MAX_NUM>>;
        using Parent::Parent;
        using Parent::IndexBegin;
        using Parent::IndexEnd;
    };
}

#endif //OBJECT_ARRAY_ORDEREDARRAYINDICES_H
