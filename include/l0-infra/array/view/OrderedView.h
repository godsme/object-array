//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_ORDEREDVIEW_H
#define OBJECT_ARRAY_ORDEREDVIEW_H

#include <l0-infra/array/holder/OrderedViewDataHolder.h>
#include <l0-infra/array/mixin/array_like/RangedArrayLike.h>
#include <l0-infra/array/mixin/array_like/ObjectIndex.h>
#include <l0-infra/array/mixin/array_like/ArrayElemVisit.h>
#include <l0-infra/array/mixin/find/ScopedFind.h>
#include <l0-infra/array/mixin/foreach/ScopedForEach.h>
#include <l0-infra/array/mixin/accessor/IndexedRefAccessor.h>
#include <l0-infra/array/mixin/accessor/ByIndexAccessor.h>
#include <l0-infra/array/mixin/count/RangedElemsCount.h>
#include <l0-infra/array/mixin/iterable/IterableArrayLike.h>
#include <l0-infra/array/mixin/find/NonScopedSimpleFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/foreach/SimpleForEach.h>
#include <l0-infra/array/mixin/foreach/SimpleForEachExt.h>
#include <l0-infra/array/mixin/factory/IndexedViewFactory.h>

namespace view::detail {
    using OrderedViewMixins = ::mixin::Mixins<
            mixin::RangedArrayLike,
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
            mixin::IndexedViewFactory>;

    template<typename ARRAY, template<typename> typename HOLDER>
    class OrderedView : public OrderedViewMixins::Compose<HOLDER<ARRAY>> {
        using Parent = OrderedViewMixins::Compose<HOLDER<ARRAY>>;
    public:
        OrderedView(ARRAY& array, typename ARRAY::SizeType n)
            : Parent{array, array, n} {}

        OrderedView(ARRAY&& array, typename ARRAY::SizeType n)
                : Parent{std::move(array), array, n} {}
    };
}

namespace view {
    template<typename ARRAY>
    using OrderedView = detail::OrderedView<ARRAY, holder::RefOrdredViewHolder>;

    template<typename ARRAY>
    using ValueOrderedView = detail::OrderedView<ARRAY, holder::ValueOrderedViewHolder>;
}

#endif //OBJECT_ARRAY_ORDEREDVIEW_H
