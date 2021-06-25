//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_VIEW_SLICE_H
#define OBJECT_ARRAY_VIEW_SLICE_H

#include <object-array/detail/RangedReadOnlyMixins.h>
#include <object-array/mixin/RvalueScopedViewFactory.h>
#include <object-array/mixin/RValueIndexedViewFactory.h>
#include <object-array/holder/RangedViewDataHolder.h>
#include <object-array/detail/ReadOnlyArrayLike.h>

namespace view::detail {
    using SliceMixins = ::detail::RangedReadOnlyMixins::Extends<
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory>;

    template<typename HOLDER>
    class Slice : public ::detail::ReadOnlyArrayLike<HOLDER, SliceMixins> {
        using Parent = ::detail::ReadOnlyArrayLike<HOLDER, SliceMixins>;
        using typename Parent::Holder;
        using typename Parent::Mixins;

    public:
        using Parent::Parent;

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

#endif //OBJECT_ARRAY_VIEW_SLICE_H
