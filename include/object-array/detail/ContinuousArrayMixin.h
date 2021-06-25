//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
#define OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H

#include <object-array/mixin/detail/Mixins.h>
#include <object-array/detail/RangedReadOnlyMixins.h>
#include <object-array/mixin/RangedArray.h>
#include <object-array/mixin/ContinuousArrayLike.h>
#include <object-array/mixin/SimpleMutate.h>
#include <object-array/mixin/SimpleMutateExt.h>
#include <object-array/mixin/RangedClear.h>
#include <object-array/mixin/PredBasedMutate.h>
#include <object-array/mixin/ScopedCleanUp.h>
#include <object-array/mixin/SimpleMinElemExt.h>
#include <object-array/mixin/ScopedMinElemExt.h>
#include <object-array/mixin/RangedViewFactory.h>
#include <object-array/mixin/ScopedViewFactory.h>
#include <object-array/mixin/ScopedViewFactory.h>
#include <object-array/mixin/IndexedViewFactory.h>

namespace detail {

    using ContinousReadOnlyMixins = mixin::Mixins <
            mixin::ContinuousArrayLike,
            mixin::RangedArray>::Concat<RangedReadOnlyMixins>;

    using ContinuousArrayMixin = ContinousReadOnlyMixins::Extends<
            mixin::SimpleMutateExt,
            mixin::RangedClear,
            mixin::PredBasedMutate,
            mixin::ScopedCleanUp>;
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYMIXIN_H
