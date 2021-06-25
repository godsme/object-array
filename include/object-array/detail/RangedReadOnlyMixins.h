//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H
#define OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H

#include <object-array/mixin/detail/Mixins.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/ScopedFind.h>
#include <object-array/mixin/ScopedFindExt.h>
#include <object-array/mixin/IterableArrayLike.h>
#include <object-array/mixin/IndexedRefAccessor.h>
#include <object-array/mixin/ByIndexAccessor.h>
#include <object-array/mixin/RangedElemsCount.h>
#include <object-array/mixin/ArrayElemVisit.h>
#include <object-array/mixin/SimpleForEach.h>
#include <object-array/mixin/SimpleForEachExt.h>
#include <object-array/mixin/ScopedForEachExt.h>
#include <object-array/mixin/SimpleMinElemExt.h>
#include <object-array/mixin/ScopedMinElemExt.h>

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
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt>;
}

#endif //OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H
