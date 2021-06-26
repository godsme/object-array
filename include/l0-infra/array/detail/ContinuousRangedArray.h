//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_CONTINUOUSRANGEDARRAY_H
#define OBJECT_ARRAY_CONTINUOUSRANGEDARRAY_H

#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/RangedArray.h>
#include <l0-infra/array/mixin/ContinuousArrayLike.h>

namespace detail {
    using ContinuousRangedArray = mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray>;
}

#endif //OBJECT_ARRAY_CONTINUOUSRANGEDARRAY_H
