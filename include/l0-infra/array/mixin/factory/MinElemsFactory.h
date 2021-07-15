//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_1737B59D08BB4129A2464AC1948C075D
#define OBJECT_ARRAY_2_1737B59D08BB4129A2464AC1948C075D

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/SortView.h>

namespace mixin::detail {
    template<typename T, template<typename> typename REF_VIEW>
    class MinElemsFactory : public T {
    protected:
        using typename T::ThisType;

    private:
        using ThisConstSortView = REF_VIEW<ThisType const>;
        using ThisSortView = REF_VIEW<ThisType>;

    public:
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        [[nodiscard]] auto MinElems(LESS&& less, SizeType n) const & -> ThisConstSortView {
            return ThisConstSortView{T::ToThisType()}.MinElems(std::forward<LESS>(less), n);
        }

        [[nodiscard]] auto MinElems(SizeType n) const & -> ThisConstSortView {
            return MinElems(T::GetLess(), n);
        }

        [[nodiscard]] auto MaxElems(SizeType n) const & -> ThisConstSortView {
            return MinElems(T::GetGreater(), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        [[nodiscard]] auto MinElems(LESS&& less, SizeType n) & -> ThisSortView {
            return ThisSortView{T::ToThisType()}.MinElems(std::forward<LESS>(less), n);
        }

        [[nodiscard]] auto MinElems(SizeType n) & -> ThisSortView {
            return MinElems(T::GetLess(), n);
        }

        [[nodiscard]] auto MaxElems(SizeType n) & -> ThisSortView {
            return MinElems(T::GetGreater(), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElems(LESS&& less, SizeType n) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto MinElems(LESS&& less, SizeType n) const && = delete;

        auto MinElems(SizeType n) && = delete;
        auto MaxElems(SizeType n) && = delete;
        auto MinElems(SizeType n) const && = delete;
        auto MaxElems(SizeType n) const && = delete;
    };
}

namespace mixin {
    template<typename T>
    using MinElemsFactory = detail::MinElemsFactory<T, SortView::RefView>;

    template<typename T>
    using ScopeMinElemsFactory = detail::MinElemsFactory<T, ScopeSortView::RefView>;
}

#endif //OBJECT_ARRAY_2_1737B59D08BB4129A2464AC1948C075D
