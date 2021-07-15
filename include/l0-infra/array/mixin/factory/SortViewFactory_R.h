//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_CABCFA6E2BBB496481E2377090D6652C
#define OBJECT_ARRAY_2_CABCFA6E2BBB496481E2377090D6652C

#include <l0-infra/array/view/SortView.h>

namespace mixin::detail {
    template<typename T, template<typename> typename VALUE_SORT_VIEW>
    struct SortViewFactory_R : T {
    protected:
        using typename T::ThisType;

    private:
        using ConstSortView = VALUE_SORT_VIEW<ThisType const>;
        using ValueSortView   = VALUE_SORT_VIEW<ThisType>;

    public:
        using T::SortView;

        auto SortView() && -> ValueSortView { return { T::ToThisType() }; }
        auto SortView() const && -> ConstSortView { return { T::ToThisType() }; }
    };
}

namespace mixin {
    template<typename T>
    using SortViewFactory_R = detail::SortViewFactory_R<T, SortView::ValueView>;

    template<typename T>
    using ScopeSortViewFactory_R = detail::SortViewFactory_R<T, ScopeSortView::ValueView>;
}

#endif //OBJECT_ARRAY_2_CABCFA6E2BBB496481E2377090D6652C
