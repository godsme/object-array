//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_WITHINDEXVIEWFACTORY_H
#define OBJECT_ARRAY_WITHINDEXVIEWFACTORY_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/WithIndexView.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class WithIndexViewFactory : public T {
    protected:
        using typename T::RangedArrayLike;

    public:
        auto WithIndex() & -> view::IndexedView::RefView<RangedArrayLike> {
            return {reinterpret_cast<RangedArrayLike&>(*this)};
        }
        auto WithIndex() const & -> view::IndexedView::RefView<RangedArrayLike const> {
            return {reinterpret_cast<RangedArrayLike const&>(*this)};
        }
        // R-Value WithIndex is not allowed.
        auto WithIndex() && -> void {}
        auto WithIndex() const && -> void {}
    };
}

#endif //OBJECT_ARRAY_WITHINDEXVIEWFACTORY_H
