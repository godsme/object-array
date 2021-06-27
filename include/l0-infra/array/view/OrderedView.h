//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_ORDEREDVIEW_H
#define OBJECT_ARRAY_ORDEREDVIEW_H

#include <l0-infra/array/holder/OrderedViewDataHolder.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLike.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLikeMixins.h>
#include <l0-infra/array/mixin/IndexedViewFactory.h>

namespace view::detail {
    using OrderedViewMixins = ::detail::SimpleReadOnlyArrayLikeMixins::Extends<
            mixin::IndexedViewFactory>;

    template<typename ARRAY, typename OWNER, template<typename, typename> typename HOLDER>
    using OrderedViewBased = ::detail::SimpleReadOnlyArrayLike<HOLDER<ARRAY, OWNER>, OrderedViewMixins, true>;

    template<typename ARRAY, template<typename, typename> typename HOLDER>
    class OrderedView : public OrderedViewBased<ARRAY, OrderedView<ARRAY, HOLDER>, HOLDER> {
        using Parent = OrderedViewBased<ARRAY, OrderedView<ARRAY, HOLDER>, HOLDER> ;
    public:
        OrderedView(ARRAY& array, typename ARRAY::SizeType n)
            : Parent{array, array, n} {}
    };
}

namespace view {
    template<typename ARRAY>
    using OrderedView = detail::OrderedView<ARRAY, holder::RefOrdredViewHolder>;

    template<typename ARRAY>
    using ValueOrderedView = detail::OrderedView<ARRAY, holder::ValueOrderedViewHolder>;
}

#endif //OBJECT_ARRAY_ORDEREDVIEW_H
