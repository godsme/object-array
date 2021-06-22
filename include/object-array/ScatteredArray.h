//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <object-array/holder/ScatteredArrayDataHolder.h>
#include <object-array/mixin/ScopedSimpleFind.h>
#include <object-array/mixin/ScopedRangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Combinator.h>
#include <object-array/mixin/ScopedRangedArray.h>

namespace detail {
    template<typename T, std::size_t MAX_NUM>
    using ScatteredArray = mixin::Combinator<
            holder::ScatteredArrayDataHolder<T, MAX_NUM>,
            mixin::ScopedRangedArray,
            mixin::ScopedRangedArrayLike,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt>;
}

template<typename T, std::size_t MAX_NUM>
struct ScatteredArray : detail::ScatteredArray<T, MAX_NUM> {
    using Parent = detail::ScatteredArray<T, MAX_NUM>;
    using Holder = typename Parent::Holder;
    using Mixins = typename Parent::Mixins;

public:
    using Parent::Parent;

    using Mixins::Find;
    using Mixins::FindIndex;
};

#endif //OBJECT_ARRAY_SCATTEREDARRAY_H
