//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_VIEW_SLICE_H
#define OBJECT_ARRAY_VIEW_SLICE_H

#include <l0-infra/array/holder/RangedViewDataHolder.h>
#include <l0-infra/array/holder/FromViewDataHolder.h>
#include <l0-infra/array/holder/UntilViewDataHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/find/ScopedFindExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/factory/RvalueScopedViewFactory.h>
#include <l0-infra/array/mixin/factory/RValueWithIndexViewFactory.h>
#include <l0-infra/array/mixin/factory/RValueSortViewFactory.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/sort/ArraySort.h>
#include <l0-infra/array/mixin/sort/ArraySortExt.h>
#include <l0-infra/array/mixin/sort/RValueArraySort.h>
#include <l0-infra/array/mixin/replace/RangedReplace.h>
#include <l0-infra/array/mixin/append/ViewAppend.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/detail/___ranged_array_tag___.h>
#include <l0-infra/array/mixin/append/SimpleAppend.h>
#include <l0-infra/array/mixin/replace/SimpleReplace.h>

namespace view::detail {
    using SliceMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ViewedArray,
            mixin::ViewAppend,
            mixin::RangedReplace,
            mixin::___ranged_array_tag___,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::ScopedForEach,
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
            mixin::RValueWithIndexViewFactory,
            mixin::RValueSortViewFactory,
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleAppend,
            mixin::AppendExt,
            mixin::SimpleReplace,
            mixin::ReplaceExt,
            mixin::RValueArraySort,
            mixin::ArraySortExt>;


    using OrderedSliceMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ViewedArray,
            mixin::ViewAppend,
            mixin::RangedReplace,
            mixin::___ranged_array_tag___,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::SimpleForEach,
            mixin::ScopedFind,
            mixin::ScopedForEach,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::RValueScopedViewFactory,
            mixin::RValueWithIndexViewFactory,
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleAppend,
            mixin::AppendExt,
            mixin::SimpleReplace,
            mixin::ReplaceExt>;

    template<bool ORDERED>
    struct SliceMixinTrait {
        using Type = OrderedSliceMixins;
    };

    template<>
    struct SliceMixinTrait<false> {
        using Type = SliceMixins;
    };

    template<typename ARRAY, template<typename> typename HOLDER, bool ORDERED>
    using Slice = typename SliceMixinTrait<ORDERED>::Type::template Compose<HOLDER<ARRAY>>;
}

namespace view {
    ////////////////////////////////////////////////////////////////////////
    template<typename ARRAY, bool ORDERED>
    using Slice = detail::Slice<ARRAY, holder::RefRangedViewDataHolder, ORDERED>;

    template<typename ARRAY, bool ORDERED>
    using ValueSlice = detail::Slice<ARRAY, holder::ValueRangedViewDataHolder, ORDERED>;

    ////////////////////////////////////////////////////////////////////////
    template<typename ARRAY, bool ORDERED>
    using FromView = detail::Slice<ARRAY, holder::RefFromViewDataHolder, ORDERED>;

    template<typename ARRAY, bool ORDERED>
    using ValueFromView = detail::Slice<ARRAY, holder::ValueFromViewDataHolder, ORDERED>;

    ////////////////////////////////////////////////////////////////////////
    template<typename ARRAY, bool ORDERED>
    using UntilView = detail::Slice<ARRAY, holder::RefUntilViewDataHolder, ORDERED>;

    template<typename ARRAY, bool ORDERED>
    using ValueUntilView = detail::Slice<ARRAY, holder::ValueUntilViewDataHolder, ORDERED>;
}

#endif //OBJECT_ARRAY_VIEW_SLICE_H
