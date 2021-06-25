//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_VIEW_SLICE_H
#define OBJECT_ARRAY_VIEW_SLICE_H

#include <object-array/detail/RangedReadOnlyMixins.h>
#include <object-array/mixin/RvalueScopedViewFactory.h>
#include <object-array/mixin/RValueIndexedViewFactory.h>
#include <object-array/holder/RangedViewDataHolder.h>
#include <object-array/detail/ContinuousReadOnlyArray.h>

namespace view::detail {
    using SliceMixins = ::detail::RangedReadOnlyMixins::Extends<
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory>;

    template<typename HOLDER>
    using Slice = ::detail::ContinuousReadOnlyArrayLike<HOLDER, SliceMixins>;
}

namespace view {
    template<typename ARRAY>
    using Slice = detail::Slice<holder::RefRangedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using ValueSlice = detail::Slice<holder::ValueRangedViewDataHolder<ARRAY>>;
}

#endif //OBJECT_ARRAY_VIEW_SLICE_H
