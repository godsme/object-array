//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_VIEW_SLICE_H
#define OBJECT_ARRAY_VIEW_SLICE_H

#include <l0-infra/array/detail/RangedReadOnlyMixins.h>
#include <l0-infra/array/mixin/RvalueScopedViewFactory.h>
#include <l0-infra/array/mixin/RValueIndexedViewFactory.h>
#include <l0-infra/array/holder/RangedViewDataHolder.h>
#include <l0-infra/array/mixin/ArraySort.h>
#include <l0-infra/array/mixin/ArraySortExt.h>
#include <l0-infra/array/mixin/RValueSortViewFactory.h>
#include <l0-infra/array/mixin/RValueArraySort.h>
#include <l0-infra/array/holder/FromViewDataHolder.h>
#include <l0-infra/array/holder/UntilViewDataHolder.h>
#include <l0-infra/array/mixin/detail/__MutableMixinDelimiter__.h>
#include <l0-infra/array/mixin/RangedReplace.h>
#include <l0-infra/array/mixin/ViewedArray.h>

namespace view::detail {
    using SliceMixins = ::detail::RangedReadOnlyMixins::Extends<
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory,
            mixin::RValueSortViewFactory,
            mixin::__MutableMixinDelimiter__,
            mixin::ViewedArray,
            mixin::RangedReplace,
            mixin::RValueArraySort,
            mixin::ArraySortExt>;

    template<typename ARRAY, template<typename> typename HOLDER>
    using Slice = SliceMixins::Compose<HOLDER<ARRAY>>;
}

namespace view {
    template<typename ARRAY>
    using Slice = detail::Slice<ARRAY, holder::RefRangedViewDataHolder>;

    template<typename ARRAY>
    using ValueSlice = detail::Slice<ARRAY, holder::ValueRangedViewDataHolder>;

    template<typename ARRAY>
    using FromView = detail::Slice<ARRAY, holder::RefFromViewDataHolder>;

    template<typename ARRAY>
    using ValueFromView = detail::Slice<ARRAY, holder::ValueFromViewDataHolder>;

    template<typename ARRAY>
    using UntilView = detail::Slice<ARRAY, holder::RefUntilViewDataHolder>;

    template<typename ARRAY>
    using ValueUntilView = detail::Slice<ARRAY, holder::ValueUntilViewDataHolder>;
}

#endif //OBJECT_ARRAY_VIEW_SLICE_H
