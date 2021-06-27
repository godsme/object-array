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
#include <l0-infra/array/detail/ReadOnlyArrayLike.h>
#include <l0-infra/array/mixin/ScopedSortViewFactory.h>
#include <l0-infra/array/mixin/ScopedSort.h>
#include <l0-infra/array/mixin/RValueScopedSort.h>

namespace view::detail {
    using ScopedMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::RangedScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ArrayElemVisit,
            mixin::ScopedSimpleForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedSimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSortViewFactory,
            mixin::RValueScopedSort,
            mixin::ArraySortExt>;

    template<typename ARRAY, template <typename, typename> typename HOLDER>
    class ScopedView : public ::detail::ReadOnlyArrayLike<HOLDER<ARRAY, ScopedView<ARRAY, HOLDER>>, ScopedMixins> {
        using Parent = ::detail::ReadOnlyArrayLike<HOLDER<ARRAY, ScopedView<ARRAY, HOLDER>>, ScopedMixins>;
        using typename Parent::Mixins;
    public:
        using Parent::Parent;
        using Mixins::SortObject;

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
    using ScopedView = detail::ScopedView<ARRAY, holder::RefScopedViewDataHolder>;

    template<typename ARRAY>
    using ValueScopedView = detail::ScopedView<ARRAY, holder::ValueScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEW_H
