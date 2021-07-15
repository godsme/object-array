//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_1C403A76CEEB4BDBB3768F955AA7C234
#define OBJECT_ARRAY_2_1C403A76CEEB4BDBB3768F955AA7C234

#include <l0-infra/array/view/SortView.h>

namespace mixin::detail {
    template<typename T, template<typename> typename REF_SORT_VIEW>
    struct SortViewFactory : T {
    protected:
        using typename T::ThisType;

    private:
        using ConstSortView = REF_SORT_VIEW<ThisType const>;
        using RefSortView   = REF_SORT_VIEW<ThisType>;

    public:
        auto SortView() & -> RefSortView { return { T::ToThisType() }; }
        auto SortView() const & -> ConstSortView { return { T::ToThisType() }; }

        auto SortView() && = delete;
        auto SortView() const && = delete;
    };
}

namespace mixin {
    template<typename T>
    using SortViewFactory = detail::SortViewFactory<T, SortView::RefView>;

    template<typename T>
    using ScopeSortViewFactory = detail::SortViewFactory<T, ScopeSortView::RefView>;
}

#endif //OBJECT_ARRAY_2_1C403A76CEEB4BDBB3768F955AA7C234
