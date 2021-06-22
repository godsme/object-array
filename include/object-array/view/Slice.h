//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SLICE_H
#define OBJECT_ARRAY_SLICE_H

#include <object-array/holder/RangedViewDataHolder.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Combinator.h>
#include <object-array/mixin/ScopedViewFactory.h>

namespace view::detail {
    template<typename HOLDER>
    using SliceMixin = mixin::Combinator<
            HOLDER,
            mixin::RangedArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopedViewFactory>;

    template<typename ARRAY>
    using ValueSlice = SliceMixin<holder::ValueRangedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using RefSlice = SliceMixin<holder::RefRangedViewDataHolder<ARRAY>>;

    template<typename HOLDER, typename Parent = SliceMixin<HOLDER>>
    class Slice : Parent {
        using Holder = typename Parent::Holder;
        using Mixins = typename Parent::Mixins;

    public:
        using Parent::Parent;

        using Mixins::Find;
        using Mixins::FindIndex;
        using Mixins::Scope;
        using Mixins::Exclude;
    };
}

namespace view {
    template<typename ARRAY>
    using Slice = detail::Slice<holder::RefRangedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using ValueSlice = detail::Slice<holder::ValueRangedViewDataHolder<ARRAY>>;
}

#endif //OBJECT_ARRAY_SLICE_H
