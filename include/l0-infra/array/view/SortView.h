//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTVIEW_H
#define OBJECT_ARRAY_SORTVIEW_H

#include <l0-infra/array/holder/SortViewDataHolder.h>
#include <l0-infra/array/mixin/factory/WithIndexViewFactory.h>
#include <l0-infra/array/mixin/sort/ArraySortExt.h>
#include <l0-infra/array/mixin/sort/IndicesBasedSort.h>
#include <l0-infra/array/mixin/detail/___ranged_array_tag___.h>
#include <l0-infra/array/mixin/iterable/IterableIndexBasedArray.h>
#include <l0-infra/array/mixin/array_like/IndexedObjectIndex.h>

namespace view::detail {
    using SortViewMixins = ::mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::___ranged_array_tag___,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::SimpleForEach,
            mixin::ScopedForEach,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableIndexBasedArray,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::WithIndexViewFactory,
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
