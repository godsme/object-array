//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
#define OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H

#include <object-array/mixin/detail/Combinator.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/RangedArray.h>
#include <object-array/mixin/ContinuousArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/RangedViewFactory.h>
#include <object-array/mixin/ScopedViewFactory.h>

namespace detail {
    template<typename HOLDER>
    using ContinuousArrayMixin = mixin::Combinator<
            HOLDER,
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::RangedViewFactory,
            mixin::ScopedViewFactory>;
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
