//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <object-array/holder/ObjectArrayDataHolder.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/RangedArray.h>
#include <object-array/mixin/ContinuousArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Combinator.h>

namespace detail {
    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = mixin::Combinator<true,
            holder::ObjectArrayDataHolder<T, MAX_NUM>,
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt>;
}

template<typename T, std::size_t MAX_NUM>
struct ObjectArray : detail::ObjectArray<T, MAX_NUM> {
    using Parent = detail::ObjectArray<T, MAX_NUM>;
    using Parent::Parent;
    using Holder = typename Parent::Holder;

    using Holder::Elems;
    using Holder::Num;
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
