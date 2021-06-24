//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
#define OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H

#include <object-array/mixin/detail/Mixins.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/RangedArray.h>
#include <object-array/mixin/ContinuousArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/ScopedFind.h>
#include <object-array/mixin/ScopedFindExt.h>
#include <object-array/mixin/RangedViewFactory.h>
#include <object-array/mixin/ScopedViewFactory.h>
#include <object-array/mixin/ScopedViewFactory.h>
#include <object-array/mixin/IndexedViewFactory.h>
#include <object-array/mixin/IterableArrayLike.h>
#include <object-array/mixin/IndexedRefAccessor.h>
#include <object-array/mixin/ByIndexAccessor.h>
#include <object-array/mixin/RangedElemsCount.h>

namespace detail {
    using ContinuousArrayMixin = mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopedFindExt>;
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
