//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_7FF5F771B8EB47679A8BC309DAADFC1D
#define OBJECT_ARRAY_2_7FF5F771B8EB47679A8BC309DAADFC1D

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/SortView.h>

namespace mixin::detail {
    template<typename T, template<typename> typename REF_SORT_VIEW>
    struct MinElemsFactory_R : T {
    protected:
        using typename T::ThisType;

    private:
        using ConstSortView = SortView::ValueView<ThisType const>;
        using SortView = SortView::ValueView<ThisType>;

    public:
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        using T::MinElems;
        using T::MaxElems;

        template<__lEsS_cOnCePt(LESS)>
        [[nodiscard]] auto MinElems(LESS&& less, SizeType n) const && -> ConstSortView {
            return ConstSortView{std::move(T::ToThisType())}.MinElems(std::forward<LESS>(less), n);
        }

        [[nodiscard]] auto MinElems(SizeType n) const && -> ConstSortView {
            return std::move(*this).MinElems(std::less<ObjectType>{}, n);
        }

        [[nodiscard]] auto MaxElems(SizeType n) const && -> ConstSortView {
            return std::move(*this).MinElems(std::greater<ObjectType>{}, n);
        }

        template<__lEsS_cOnCePt(LESS)>
        [[nodiscard]] auto MinElems(LESS&& less, SizeType n) && -> SortView {
            return SortView{std::move(T::ToThisType())}.MinElems(std::forward<LESS>(less), n);
        }

        [[nodiscard]] auto MinElems(SizeType n) && -> SortView {
            return std::move(*this).MinElems(std::less<ObjectType>{}, n);
        }

        [[nodiscard]] auto MaxElems(SizeType n) && -> SortView {
            return std::move(*this).MinElems(std::greater<ObjectType>{}, n);
        }
    };
}

namespace mixin {
    template<typename T>
    using MinElemsFactory_R = detail::MinElemsFactory_R<T, SortView::ValueView>;

    template<typename T>
    using ScopeMinElemsFactory_R = detail::MinElemsFactory_R<T, ScopeSortView::ValueView>;
}

#endif //OBJECT_ARRAY_2_7FF5F771B8EB47679A8BC309DAADFC1D
