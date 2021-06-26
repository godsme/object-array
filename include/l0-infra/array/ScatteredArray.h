//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <l0-infra/array/holder/ScatteredArrayDataHolder.h>
#include <l0-infra/array/detail/ReadOnlyArrayLike.h>
#include <l0-infra/array/mixin/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/SimpleFindExt.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/RangedArray.h>
#include <l0-infra/array/mixin/RangedArrayLike.h>
#include <l0-infra/array/mixin/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/ByIndexAccessor.h>
#include <l0-infra/array/mixin/ScopedByIndexAccessor.h>
#include <l0-infra/array/mixin/ArrayElemVisit.h>
#include <l0-infra/array/mixin/ScopedSimpleForEach.h>
#include <l0-infra/array/mixin/SimpleForEachExt.h>
#include <l0-infra/array/mixin/FullScopedElemCount.h>
#include <l0-infra/array/mixin/ScopedSimpleMinElem.h>
#include <l0-infra/array/mixin/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/IndexedScopedViewFactory.h>
#include <l0-infra/array/mixin/SimpleMutateExt.h>
#include <l0-infra/array/mixin/PredBasedMutate.h>
#include <l0-infra/array/mixin/ScopedCleanUp.h>

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

    template<typename T, std::size_t MAX_NUM, typename OWNER>
    using ScatteredArrayBase = detail::ReadOnlyArrayLike<
            holder::ScatteredArrayHolder<T, MAX_NUM, OWNER>,
            detail::ScatteredArrayMixins>;
}

template<typename T, std::size_t MAX_NUM>
class ScatteredArray : public detail::ScatteredArrayBase<T, MAX_NUM, ScatteredArray<T, MAX_NUM>> {
    using Parent = detail::ScatteredArrayBase<T, MAX_NUM, ScatteredArray<T, MAX_NUM>>;
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
