//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_ORDEREDSCOPEDVIEW_H
#define OBJECT_ARRAY_ORDEREDSCOPEDVIEW_H

#include <l0-infra/array/holder/ScopedViewDataHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/find/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/factory/WithIndexScopedViewFactory.h>
#include <l0-infra/array/mixin/iterable/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/accessor/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/accessor/ScopedByIndexAccessor.h>
#include <l0-infra/array/mixin/count/RangedScopedElemCount.h>
#include <l0-infra/array/mixin/foreach/ScopedSimpleForEach.h>

namespace view::detail {
    using SimpleScopedViewMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
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
            mixin::WithIndexScopedViewFactory>;

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
