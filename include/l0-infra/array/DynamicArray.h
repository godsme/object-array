//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAY_H
#define OBJECT_ARRAY_DYNAMICARRAY_H

#include <l0-infra/array/holder/DynamicArrayDataHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>
#include <l0-infra/array/mixin/array_like/DynamicObjectIndex.h>


namespace detail {
    using DynamicArrayMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::___ranged_array_tag___,
            mixin::DynamicObjectIndex,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableIndexBasedArray,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleAppend>;
}

template<typename ALLOCATOR, std::size_t MAX_NUM>
using DynamicArray = detail::DynamicArrayMixins::Compose<holder::DynamicArrayDataHolder<ALLOCATOR, MAX_NUM>>;

#endif //OBJECT_ARRAY_DYNAMICARRAY_H
