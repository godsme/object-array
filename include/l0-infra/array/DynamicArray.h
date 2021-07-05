//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAY_H
#define OBJECT_ARRAY_DYNAMICARRAY_H

#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/array_like/RangedArray.h>

namespace detail {
    using DynamicArrayMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray>;
}

#endif //OBJECT_ARRAY_DYNAMICARRAY_H
