//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
#define OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H

#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/detail/ContinuousRangedArray.h>
#include <l0-infra/array/mixin/SimpleMutate.h>
#include <l0-infra/array/mixin/RangedClear.h>
#include <l0-infra/array/mixin/EraseExt.h>
#include <l0-infra/array/mixin/ScopedCleanUp.h>
#include <l0-infra/array/mixin/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/RangedViewFactory.h>
#include <l0-infra/array/mixin/ScopedViewFactory.h>
#include <l0-infra/array/mixin/ScopedViewFactory.h>
#include <l0-infra/array/mixin/IndexedViewFactory.h>
#include <l0-infra/array/mixin/ArraySort.h>
#include <l0-infra/array/mixin/ArraySortExt.h>
#include <l0-infra/array/mixin/ReplaceExt.h>
#include <l0-infra/array/mixin/AppendExt.h>

namespace detail {
    using ContinousReadOnlyMixins = ContinuousRangedArray::Concat<RangedReadOnlyMixins>;

    using ContinuousArrayMixin = ContinousReadOnlyMixins::Extends<
            mixin::SimpleMutate,
            mixin::ReplaceExt,
            mixin::AppendExt,
            mixin::EraseExt,
            mixin::ScopedCleanUp,
            mixin::RangedClear>;
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
