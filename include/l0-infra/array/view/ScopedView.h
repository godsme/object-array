//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEW_H
#define OBJECT_ARRAY_SCOPEDVIEW_H

#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/holder/ScopedViewDataHolder.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/array_like/RangedArrayLike.h>
#include <l0-infra/array/mixin/array_like/ArrayElemVisit.h>
#include <l0-infra/array/mixin/detail/___public_mixin_delimiter___.h>
#include <l0-infra/array/mixin/find/ScopedFind.h>
#include <l0-infra/array/mixin/find/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/minmax/ScopedMinElem.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/accessor/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/factory/WithIndexScopedViewFactory.h>
#include <l0-infra/array/mixin/iterable/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/accessor/ScopedByIndexAccessor.h>
#include <l0-infra/array/mixin/count/RangedScopedElemCount.h>
#include <l0-infra/array/mixin/minmax/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/foreach/ScopedSimpleForEach.h>
#include <l0-infra/array/mixin/minmax/ScopedSimpleMinElem.h>
#include <l0-infra/array/mixin/factory/ScopedSortViewFactory.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/sort/ScopedSort.h>
#include <l0-infra/array/mixin/sort/RValueScopedSort.h>
#include <l0-infra/array/mixin/append/ViewAppend.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/replace/ScopedReplace.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/detail/___ranged_array_tag___.h>
#include <l0-infra/array/mixin/append/SimpleAppend.h>
#include <l0-infra/array/mixin/replace/SimpleReplace.h>

namespace view::detail {
    using ScopedMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ViewedArray,
            mixin::ViewAppend,
            mixin::ScopedReplace,
            mixin::___ranged_array_tag___,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::ScopedMinElem,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::RangedScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::WithIndexScopedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopedSimpleForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedSimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::WithIndexScopedViewFactory,
            mixin::ScopedSortViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleAppend,
            mixin::AppendExt,
            mixin::SimpleReplace,
            mixin::ReplaceExt,
            mixin::RValueScopedSort,
            mixin::ArraySortExt>;


    using OrderedScopedMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ViewedArray,
            mixin::ViewAppend,
            mixin::ScopedReplace,
            mixin::___ranged_array_tag___,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::ScopedMinElem,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::RangedScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::WithIndexScopedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopedSimpleForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedSimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::WithIndexScopedViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleAppend,
            mixin::AppendExt,
            mixin::SimpleReplace,
            mixin::ReplaceExt>;

    template<bool ORDERED>
    struct ScopedMixinTrait {
        using Type = OrderedScopedMixins;
    };

    template<>
    struct ScopedMixinTrait<false> {
        using Type = ScopedMixins;
    };

    template<typename ARRAY, template <typename> typename HOLDER, bool ORDERED>
    using ScopedView = typename ScopedMixinTrait<ORDERED>::Type::template Compose<HOLDER<ARRAY>>;
}

namespace view {
    template<typename ARRAY, bool ORDERED>
    using ScopedView = detail::ScopedView<ARRAY, holder::RefScopedViewDataHolder, ORDERED>;

    template<typename ARRAY, bool ORDERED>
    using ValueScopedView = detail::ScopedView<ARRAY, holder::ValueScopedViewDataHolder, ORDERED>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEW_H
