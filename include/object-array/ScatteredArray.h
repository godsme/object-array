//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <object-array/holder/ScatteredArrayDataHolder.h>
#include <object-array/detail/ArrayComposer.h>
#include <object-array/mixin/ScopedSimpleFind.h>
#include <object-array/mixin/ScopedRangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Combinator.h>
#include <object-array/mixin/ScopedRangedArray.h>
#include <object-array/mixin/IterableScopedArrayLike.h>

namespace detail {
    template<typename T>
    using ScatteredArrayMixins = mixin::Combinator<
            T,
            mixin::ScopedRangedArray,
            mixin::ScopedRangedArrayLike,
            mixin::IterableScopedArrayLike,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt>;
}

template<typename T, std::size_t MAX_NUM>
class ScatteredArray : detail::ArrayComposer<holder::ScatteredArrayDataHolder<T, MAX_NUM>, detail::ScatteredArrayMixins> {
    using Parent = detail::ArrayComposer<holder::ScatteredArrayDataHolder<T, MAX_NUM>, detail::ScatteredArrayMixins>;
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
