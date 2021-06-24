//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SLICE_H
#define OBJECT_ARRAY_SLICE_H

#include <object-array/holder/RangedViewDataHolder.h>
#include <object-array/detail/ArrayComposer.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Mixins.h>
#include <object-array/mixin/IterableArrayLike.h>
#include <object-array/mixin/RValueIndexedViewFactory.h>
#include <object-array/mixin/RvalueScopedViewFactory.h>
#include <object-array/mixin/IndexedRefAccessor.h>
#include <object-array/mixin/ByIndexAccessor.h>

namespace view::detail {
    using SliceMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory>;

    template<typename HOLDER>
    class Slice : ::detail::ArrayComposer<HOLDER, SliceMixins> {
        using Parent = ::detail::ArrayComposer<HOLDER, SliceMixins>;
        using Holder = typename Parent::Holder;
        using Mixins = typename Parent::Mixins;

    public:
        using Parent::Parent;

        using Parent::operator[];
        using Parent::At;

        using Parent::begin;
        using Parent::end;

        using Mixins::Find;
        using Mixins::FindIndex;
        using Mixins::Scope;
        using Mixins::Exclude;
        using Mixins::WithIndex;
    };
}

namespace view {
    template<typename ARRAY>
    using Slice = detail::Slice<holder::RefRangedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using ValueSlice = detail::Slice<holder::ValueRangedViewDataHolder<ARRAY>>;
}

#endif //OBJECT_ARRAY_SLICE_H
