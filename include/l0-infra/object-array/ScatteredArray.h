//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <l0-infra/object-array/holder/ScatteredArrayDataHolder.h>
#include <l0-infra/object-array/detail/ReadOnlyArrayLike.h>
#include <l0-infra/object-array/mixin/ScopedSimpleFind.h>
#include <l0-infra/object-array/mixin/SimpleFindExt.h>
#include <l0-infra/object-array/mixin/detail/Mixins.h>
#include <l0-infra/object-array/mixin/IterableScopedArrayLike.h>
#include <l0-infra/object-array/mixin/RangedArray.h>
#include <l0-infra/object-array/mixin/RangedArrayLike.h>
#include <l0-infra/object-array/mixin/IndexedRefAccessor.h>
#include <l0-infra/object-array/mixin/ByIndexAccessor.h>
#include <l0-infra/object-array/mixin/ScopedByIndexAccessor.h>
#include <l0-infra/object-array/mixin/ArrayElemVisit.h>
#include <l0-infra/object-array/mixin/ScopedSimpleForEach.h>
#include <l0-infra/object-array/mixin/SimpleForEachExt.h>
#include <l0-infra/object-array/mixin/FullScopedElemCount.h>
#include <l0-infra/object-array/mixin/ScopedSimpleMinElem.h>
#include <l0-infra/object-array/mixin/SimpleMinElemExt.h>
#include <l0-infra/object-array/mixin/IndexedScopedViewFactory.h>
#include <l0-infra/object-array/mixin/SimpleMutateExt.h>
#include <l0-infra/object-array/mixin/PredBasedMutate.h>
#include <l0-infra/object-array/mixin/ScopedCleanUp.h>

namespace detail {
    using ScatteredArrayMixins = mixin::Mixins<
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::FullScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ArrayElemVisit,
            mixin::ScopedSimpleForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedSimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::IndexedScopedViewFactory,
            mixin::SimpleMutateExt,
            mixin::PredBasedMutate,
            mixin::ScopedCleanUp>;

    template<typename T, std::size_t MAX_NUM>
    using ScatteredArrayBase = detail::ReadOnlyArrayLike<
            holder::ScatteredArrayHolder<T, MAX_NUM>,
            detail::ScatteredArrayMixins>;
}

template<typename T, std::size_t MAX_NUM, typename Parent = detail::ScatteredArrayBase<T, MAX_NUM>>
class ScatteredArray : public Parent {
    using typename Parent::Holder;
    using typename Parent::Mixins;

public:
    using Parent::Parent;

    using Mixins::Append;
    using Mixins::Replace;
    using Mixins::Erase;
    using Mixins::CleanUpBy;
    using Mixins::ReplaceObj;
    using Mixins::Remove;
    using Mixins::RemoveBy;
    using Mixins::CleanUp;
    using Mixins::CleanUpEx;
    using Mixins::FindOrAppend;
    using Holder::Clear;
};

#endif //OBJECT_ARRAY_SCATTEREDARRAY_H
