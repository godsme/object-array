//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H
#define OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H

#include <l0-infra/array/detail/SimpleReadOnlyArrayLikeMixins.h>
#include <l0-infra/array/mixin/ScopedForEachExt.h>
#include <l0-infra/array/mixin/ScopedFindExt.h>
#include <l0-infra/array/mixin/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/ScopedMinElemExt.h>

namespace detail {
    using RangedReadOnlyMixins = SimpleReadOnlyArrayLikeMixins::Extends<
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt>;
}

#endif //OBJECT_ARRAY_DETAIL_RANGEDREADONLYMIXINS_H
