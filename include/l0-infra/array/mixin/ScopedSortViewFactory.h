//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SCOPEDSORTVIEWFACTORY_H
#define OBJECT_ARRAY_SCOPEDSORTVIEWFACTORY_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/view/SortView.h>

namespace mixin {
    template<__cOnCePt(SimpleScopedRangedArrayLike) T>
    struct ScopedSortViewFactory : T {
        using Self = T;

    public:
        using typename T::RangedArrayLike;
        using T::GetScope;

    public:
        auto SortObject() && -> view::ValueSortView<RangedArrayLike> {

        }
        auto SortObject() const && -> void {}

        auto SortObject() & -> view::SortView<RangedArrayLike> {
            return {static_cast<RangedArrayLike&>(*this)};
        }

        auto SortObject() const & -> view::SortView<RangedArrayLike const> {
            return {static_cast<RangedArrayLike const&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSORTVIEWFACTORY_H
