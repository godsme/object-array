//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEW_H
#define OBJECT_ARRAY_SCOPEDVIEW_H

#include <l0-infra/array/holder/ScopedViewDataHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/SimpleFindExt.h>
#include <l0-infra/array/mixin/IndexedScopedViewFactory.h>
#include <l0-infra/array/mixin/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/ScopedByIndexAccessor.h>
#include <l0-infra/array/mixin/RangedScopedElemCount.h>
#include <l0-infra/array/mixin/ScopedSimpleForEach.h>
#include <l0-infra/array/mixin/ScopedSimpleMinElem.h>
#include <l0-infra/array/mixin/ScopedSortViewFactory.h>
#include <l0-infra/array/mixin/ScopedSort.h>
#include <l0-infra/array/mixin/RValueScopedSort.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/ViewedArray.h>
#include <l0-infra/array/mixin/ViewAppend.h>
#include <l0-infra/array/mixin/AppendExt.h>
#include <l0-infra/array/mixin/ScopedReplace.h>
#include <l0-infra/array/mixin/ReplaceExt.h>

namespace view::detail {
    using ScopedMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::ScopedMinElem,
            mixin::ViewedArray,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::RangedScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopedSimpleForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedSimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSortViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::ViewAppend,
            mixin::AppendExt,
            mixin::ScopedReplace,
            mixin::ReplaceExt,
            mixin::RValueScopedSort,
            mixin::ArraySortExt>;

    template<typename ARRAY, template <typename> typename HOLDER>
    using ScopedView = ScopedMixins::Compose<HOLDER<ARRAY>>;
}

namespace view {
    template<typename ARRAY>
    using ScopedView = detail::ScopedView<ARRAY, holder::RefScopedViewDataHolder>;

    template<typename ARRAY>
    using ValueScopedView = detail::ScopedView<ARRAY, holder::ValueScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEW_H
