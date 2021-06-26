//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SIMPLEREADONLYARRAYLIKEMIXINS_H
#define OBJECT_ARRAY_SIMPLEREADONLYARRAYLIKEMIXINS_H

#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/RangedArrayLike.h>
#include <l0-infra/array/mixin/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/ByIndexAccessor.h>
#include <l0-infra/array/mixin/RangedElemsCount.h>
#include <l0-infra/array/mixin/IterableArrayLike.h>
#include <l0-infra/array/mixin/NonScopedSimpleFind.h>
#include <l0-infra/array/mixin/SimpleFindExt.h>
#include <l0-infra/array/mixin/ArrayElemVisit.h>
#include <l0-infra/array/mixin/SimpleForEach.h>
#include <l0-infra/array/mixin/SimpleForEachExt.h>

namespace detail {
    using SimpleReadOnlyArrayLikeMixins = ::mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ArrayElemVisit,
            mixin::SimpleForEach,
            mixin::SimpleForEachExt>;
}

#endif //OBJECT_ARRAY_SIMPLEREADONLYARRAYLIKEMIXINS_H
