//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_ORDEREDSCOPEDVIEW_H
#define OBJECT_ARRAY_ORDEREDSCOPEDVIEW_H

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

namespace view::detail {
    using SimpleScopedViewMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::__PublicMixinDelimiter__,
            mixin::IndexedRefAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::RangedScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopedSimpleForEach,
            mixin::SimpleForEachExt,
            mixin::IndexedScopedViewFactory>;

    template<typename ARRAY, template <typename, bool> typename HOLDER>
    using OrderedScopedView =  SimpleScopedViewMixins::Compose<HOLDER<ARRAY, true>>;
}

namespace view {
    template<typename ARRAY>
    struct OrderedScopedView : detail::OrderedScopedView<ARRAY, holder::RefScopedViewDataHolder> {
        using Parent = detail::OrderedScopedView<ARRAY, holder::RefScopedViewDataHolder>;
        OrderedScopedView(ARRAY& array, typename ARRAY::SizeType n)
                : Parent(array, array.GetScope().GetLowestBits(n))
        {}
    };

    template<typename ARRAY>
    using OrderedValueScopedView = detail::OrderedScopedView<ARRAY, holder::ValueProxyScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_ORDEREDSCOPEDVIEW_H