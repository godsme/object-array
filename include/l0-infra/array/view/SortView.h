//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTVIEW_H
#define OBJECT_ARRAY_SORTVIEW_H

#include <l0-infra/array/holder/SortViewDataHolder.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLike.h>
#include <l0-infra/array/detail/SimpleReadOnlyArrayLikeMixins.h>
#include <l0-infra/array/mixin/IndexedViewFactory.h>
#include <l0-infra/array/mixin/ArraySortExt.h>

namespace view::detail {
    using ArraySortObjectMixins = ::detail::SimpleReadOnlyArrayLikeMixins::Extends<
            mixin::IndexedViewFactory,
            mixin::ArraySortExt>;

    template<typename ARRAY, typename OWNER, template<typename, typename> typename HOLDER>
    using SortViewBased = ::detail::SimpleReadOnlyArrayLike<HOLDER<ARRAY, OWNER>, ArraySortObjectMixins, true>;

    template<typename ARRAY, template<typename, typename> typename HOLDER>
    class SortView : public SortViewBased<ARRAY, SortView<ARRAY, HOLDER>, HOLDER> {
        using Parent = SortViewBased<ARRAY, SortView<ARRAY, HOLDER>, HOLDER> ;
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
    using SortView = detail::SortView<ARRAY, holder::RefSortViewHolder>;

    template<typename ARRAY>
    using ValueSortView = detail::SortView<ARRAY, holder::ValueSortViewHolder>;
}

#endif //OBJECT_ARRAY_SORTVIEW_H
