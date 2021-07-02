//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_VIEW_SLICE_H
#define OBJECT_ARRAY_VIEW_SLICE_H

#include <l0-infra/array/mixin/factory/RvalueScopedViewFactory.h>
#include <l0-infra/array/mixin/factory/RValueIndexedViewFactory.h>
#include <l0-infra/array/holder/RangedViewDataHolder.h>
#include <l0-infra/array/mixin/sort/ArraySort.h>
#include <l0-infra/array/mixin/sort/ArraySortExt.h>
#include <l0-infra/array/mixin/factory/RValueSortViewFactory.h>
#include <l0-infra/array/mixin/sort/RValueArraySort.h>
#include <l0-infra/array/holder/FromViewDataHolder.h>
#include <l0-infra/array/holder/UntilViewDataHolder.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/mutable/RangedReplace.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/mutable/ViewAppend.h>
#include <l0-infra/array/mixin/mutable/AppendExt.h>
#include <l0-infra/array/mixin/mutable/ReplaceExt.h>
#include <l0-infra/array/mixin/find/ScopedFindExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElemExt.h>

namespace view::detail {

    using SliceMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::ScopedForEach,
            mixin::ViewedArray,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEach,
            mixin::SimpleForEachExt,
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory,
            mixin::RValueSortViewFactory,
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::___mutable_mixin_delimiter___,
            mixin::ViewAppend,
            mixin::AppendExt,
            mixin::RangedReplace,
            mixin::ReplaceExt,
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
