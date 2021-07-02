//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_ARRAYINDICES_H
#define OBJECT_ARRAY_ARRAYINDICES_H

#include <l0-infra/array/holder/ArrayIndicesDataHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/simple/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/ranged/RangedArray.h>
#include <l0-infra/array/mixin/ranged/RangedArrayLike.h>
#include <l0-infra/array/mixin/indexed/ObjectIndex.h>
#include <l0-infra/array/mixin/detail/___public_mixin_delimiter___.h>
#include <l0-infra/array/mixin/indexed/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/simple/ByIndexAccessor.h>
#include <l0-infra/array/mixin/ranged/RangedElemsCount.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/mutable/RangedClear.h>
#include <l0-infra/array/mixin/sort/ArraySort.h>

namespace detail {
    using ArrayIndicesMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::___mutable_mixin_delimiter___,
            mixin::RangedClear,
            mixin::ArraySort>;

    template<std::size_t MAX_NUM>
    using ArrayIndices = ArrayIndicesMixins::Compose<holder::ArrayIndicesDataHolder<MAX_NUM>>;
}

#endif //OBJECT_ARRAY_ARRAYINDICES_H
