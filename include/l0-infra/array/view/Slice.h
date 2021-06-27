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
#include <l0-infra/array/mixin/ArraySortExt.h>
#include <l0-infra/array/mixin/RValueSortViewFactory.h>
#include <l0-infra/array/mixin/RValueArraySort.h>

namespace view::detail {
    using SliceMixins = ::detail::RangedReadOnlyMixins::Extends<
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory,
            mixin::RValueArraySort,
            mixin::ArraySortExt,
            mixin::RValueSortViewFactory>;

    template<typename ARRAY, template<typename, typename> typename HOLDER>
    struct Slice : ::detail::ContinuousReadOnlyArrayLike<HOLDER<ARRAY, Slice<ARRAY, HOLDER>>, SliceMixins> {
        using Parent = ::detail::ContinuousReadOnlyArrayLike<HOLDER<ARRAY, Slice<ARRAY, HOLDER>>, SliceMixins>;
        using Parent::Parent;
        using typename Parent::Mixins;

        using Mixins::Sort;
        using Mixins::DescSort;
        using Mixins::PartialSort;
        using Mixins::PartialDescSort;
        using Mixins::StableSort;
        using Mixins::StableDescSort;

        using Mixins::SortObject;
    };
}

namespace view {
    template<typename ARRAY>
    using Slice = detail::Slice<ARRAY, holder::RefRangedViewDataHolder>;

    template<typename ARRAY>
    using ValueSlice = detail::Slice<ARRAY, holder::ValueRangedViewDataHolder>;
}

#endif //OBJECT_ARRAY_VIEW_SLICE_H
