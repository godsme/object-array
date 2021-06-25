//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H
#define OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H

#include <l0-infra/object-array/mixin/detail/Mixins.h>
#include <l0-infra/object-array/mixin/NonScopedSimpleFind.h>
#include <l0-infra/object-array/mixin/RangedArrayLike.h>
#include <l0-infra/object-array/mixin/SimpleFindExt.h>
#include <l0-infra/object-array/mixin/ScopedFind.h>
#include <l0-infra/object-array/mixin/ScopedFindExt.h>
#include <l0-infra/object-array/mixin/IterableArrayLike.h>
#include <l0-infra/object-array/mixin/IndexedRefAccessor.h>
#include <l0-infra/object-array/mixin/ByIndexAccessor.h>
#include <l0-infra/object-array/mixin/RangedElemsCount.h>
#include <l0-infra/object-array/mixin/ArrayElemVisit.h>
#include <l0-infra/object-array/mixin/SimpleForEach.h>
#include <l0-infra/object-array/mixin/SimpleForEachExt.h>
#include <l0-infra/object-array/mixin/ScopedForEachExt.h>
#include <l0-infra/object-array/mixin/SimpleMinElemExt.h>
#include <l0-infra/object-array/mixin/ScopedMinElemExt.h>

namespace detail {
    using RangedReadOnlyMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopedFindExt,
            mixin::ArrayElemVisit,
            mixin::SimpleForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt>;
}

#endif //OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H
