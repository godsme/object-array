//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <object-array/holder/ScatteredArrayDataHolder.h>
#include <object-array/detail/ArrayComposer.h>
#include <object-array/mixin/ScopedSimpleFind.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Mixins.h>
#include <object-array/mixin/IterableScopedArrayLike.h>
#include <object-array/mixin/RangedArray.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/IndexedRefAccessor.h>
#include <object-array/mixin/ByIndexAccessor.h>
#include <object-array/mixin/ScopedByIndexAccessor.h>

namespace detail {
    using ScatteredArrayMixins = mixin::Mixins<
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::IterableScopedArrayLike,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt>;

    template<typename T, std::size_t MAX_NUM>
    using ScatteredArrayBase = detail::ArrayComposer<holder::ScatteredArrayDataHolder<T, MAX_NUM>, detail::ScatteredArrayMixins>;
}

template<typename T, std::size_t MAX_NUM>
class ScatteredArray : detail::ScatteredArrayBase<T, MAX_NUM> {
    using Parent = detail::ScatteredArrayBase<T, MAX_NUM>;
    using Holder = typename Parent::Holder;
    using Mixins = typename Parent::Mixins;

public:
    using Parent::Parent;

    using Mixins::begin;
    using Mixins::end;

    using Mixins::Find;
    using Mixins::FindIndex;
};

#endif //OBJECT_ARRAY_SCATTEREDARRAY_H
