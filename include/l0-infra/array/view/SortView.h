//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTVIEW_H
#define OBJECT_ARRAY_SORTVIEW_H

#include <l0-infra/array/holder/SortViewDataHolder.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLikeMixins.h>
#include <l0-infra/array/mixin/IndexedViewFactory.h>
#include <l0-infra/array/mixin/ArraySortExt.h>
#include <l0-infra/array/mixin/IndicesBasedSort.h>

namespace view::detail {
    using SortViewMixins = ::detail::SimpleReadOnlyArrayLikeMixins::Extends<
            mixin::IndexedViewFactory,
            mixin::IndicesBasedSort,
            mixin::ArraySortExt>;

    template<typename ARRAY, template<typename> typename HOLDER>
    class SortView : public SortViewMixins::Compose<HOLDER<ARRAY>> {
        using Parent = SortViewMixins::Compose<HOLDER<ARRAY>>;
        using typename Parent::Mixins;
        using typename Parent::Holder;

    public:
        SortView(ARRAY& array) : Parent{array} {
            Holder::indices.InitWithRange(array);
        }

        SortView(ARRAY& array, typename ARRAY::BitMap scope) : Parent{array} {
            Holder::indices.InitWithRange(array, scope);
        }

        SortView(ARRAY&& array) : Parent{std::move(array)} {
            Holder::indices.InitWithRange(array);
        }

        SortView(ARRAY&& array, typename ARRAY::BitMap scope) : Parent{std::move(array)} {
            Holder::indices.InitWithRange(array, scope);
        }
    };
}

namespace view {
    template<typename ARRAY>
    using SortView = detail::SortView<ARRAY, holder::RefSortViewHolder>;

    template<typename ARRAY>
    using ValueSortView = detail::SortView<ARRAY, holder::ValueSortViewHolder>;
}

#endif //OBJECT_ARRAY_SORTVIEW_H
