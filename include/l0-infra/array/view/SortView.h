//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTVIEW_H
#define OBJECT_ARRAY_SORTVIEW_H

#include <l0-infra/array/holder/SortViewDataHolder.h>
#include <l0-infra/array/mixin/indexed/IndexedViewFactory.h>
#include <l0-infra/array/mixin/mutable/ArraySortExt.h>
#include <l0-infra/array/mixin/mutable/IndicesBasedSort.h>

namespace view::detail {
    using SortViewMixins = ::mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::SimpleForEach,
            mixin::ScopedForEach,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::IndexedViewFactory,
            mixin::IndicesBasedSort,
            mixin::ArraySortExt>;

    template<typename ARRAY, template<typename> typename HOLDER>
    using SortView = SortViewMixins::Compose<HOLDER<ARRAY>>;
}

namespace view {
    template<typename ARRAY>
    using SortView = detail::SortView<ARRAY, holder::RefSortViewHolder>;

    template<typename ARRAY>
    using ValueSortView = detail::SortView<ARRAY, holder::ValueSortViewHolder>;
}

#endif //OBJECT_ARRAY_SORTVIEW_H
