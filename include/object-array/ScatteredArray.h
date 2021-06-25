//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAY_H
#define OBJECT_ARRAY_SCATTEREDARRAY_H

#include <object-array/holder/ScatteredArrayDataHolder.h>
#include <object-array/detail/ReadOnlyArrayLike.h>
#include <object-array/mixin/ScopedSimpleFind.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Mixins.h>
#include <object-array/mixin/IterableScopedArrayLike.h>
#include <object-array/mixin/RangedArray.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/IndexedRefAccessor.h>
#include <object-array/mixin/ByIndexAccessor.h>
#include <object-array/mixin/ScopedByIndexAccessor.h>
#include <object-array/mixin/ArrayElemVisit.h>
#include <object-array/mixin/ScopedSimpleForEach.h>
#include <object-array/mixin/SimpleForEachExt.h>
#include <object-array/mixin/FullScopedElemCount.h>
#include <object-array/mixin/ScopedSimpleMinElem.h>
#include <object-array/mixin/SimpleMinElemExt.h>
#include <object-array/mixin/IndexedScopedViewFactory.h>
#include <object-array/mixin/SimpleMutateExt.h>
#include <object-array/mixin/PredBasedMutate.h>
#include <object-array/mixin/ScopedCleanUp.h>

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
