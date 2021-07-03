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

namespace detail {
    using OrderedArrayIndicesMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ContiguousDoErase,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleErase,
            mixin::RangedClear,
            mixin::OrderedDoAppend>;

    template<std::size_t MAX_NUM>
    using OrderedArrayIndices = OrderedArrayIndicesMixins::Compose<holder::OrderedArrayIndicesDataHolder<MAX_NUM>>;
}

#endif //OBJECT_ARRAY_ORDEREDARRAYINDICES_H
