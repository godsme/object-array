//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_VIEW_SLICE_H
#define OBJECT_ARRAY_VIEW_SLICE_H

#include <l0-infra/array/detail/RangedReadOnlyMixins.h>
#include <l0-infra/array/mixin/RvalueScopedViewFactory.h>
#include <l0-infra/array/mixin/RValueIndexedViewFactory.h>
#include <l0-infra/array/holder/RangedViewDataHolder.h>
#include <l0-infra/array/detail/ContinuousReadOnlyArray.h>
#include <l0-infra/array/mixin/ArraySort.h>

namespace view::detail {
    using SliceMixins = ::detail::RangedReadOnlyMixins::Extends<
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory,
            mixin::ArraySort>;

    template<typename HOLDER, typename Parent = ::detail::ContinuousReadOnlyArrayLike<HOLDER, SliceMixins>>
    class Slice : public Parent {
        using Parent::Parent;
        using typename Parent::Mixins;

        using Mixins::Sort;
        using Mixins::DescSort;
        using Mixins::PartialSort;
        using Mixins::PartialDescSort;
        using Mixins::StableSort;
        using Mixins::StableDescSort;
    };
}

namespace view {
    template<typename ARRAY>
    using Slice = detail::Slice<holder::RefRangedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using ValueSlice = detail::Slice<holder::ValueRangedViewDataHolder<ARRAY>>;
}

#endif //OBJECT_ARRAY_VIEW_SLICE_H
