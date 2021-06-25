//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
#define OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H

#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/detail/RangedReadOnlyMixins.h>
#include <l0-infra/array/mixin/RangedArray.h>
#include <l0-infra/array/mixin/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/SimpleMutate.h>
#include <l0-infra/array/mixin/SimpleMutateExt.h>
#include <l0-infra/array/mixin/RangedClear.h>
#include <l0-infra/array/mixin/PredBasedMutate.h>
#include <l0-infra/array/mixin/ScopedCleanUp.h>
#include <l0-infra/array/mixin/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/RangedViewFactory.h>
#include <l0-infra/array/mixin/ScopedViewFactory.h>
#include <l0-infra/array/mixin/ScopedViewFactory.h>
#include <l0-infra/array/mixin/IndexedViewFactory.h>

namespace detail {

    using ContinousReadOnlyMixins = mixin::Mixins <
            mixin::ContinuousArrayLike,
            mixin::RangedArray>::Concat<RangedReadOnlyMixins>;

    using ContinuousArrayMixin = ContinousReadOnlyMixins::Extends<
            mixin::SimpleMutate,
            mixin::SimpleMutateExt,
            mixin::PredBasedMutate,
            mixin::ScopedCleanUp,
            mixin::RangedClear>;
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
