//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_ORDEREDVIEW_H
#define OBJECT_ARRAY_ORDEREDVIEW_H

#include <l0-infra/array/holder/OrderedViewDataHolder.h>
#include <l0-infra/array/mixin/indexed/IndexedViewFactory.h>
#include <l0-infra/array/mixin/simple/ArrayElemVisit.h>
#include <l0-infra/array/mixin/scoped/ScopedFind.h>
#include <l0-infra/array/mixin/scoped/ScopedForEach.h>
#include <l0-infra/array/mixin/simple/IterableArrayLike.h>
#include <l0-infra/array/mixin/simple/NonScopedSimpleFind.h>
#include <l0-infra/array/mixin/simple/SimpleFindExt.h>
#include <l0-infra/array/mixin/simple/SimpleForEach.h>
#include <l0-infra/array/mixin/simple/SimpleForEachExt.h>

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
