//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTVIEWFACTORY_H
#define OBJECT_ARRAY_SORTVIEWFACTORY_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/SortView.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct SortViewFactory : T {
        using Self = T;

    public:
        using typename T::RangedArrayLike;

    public:
        auto SortObject() && -> void {}
        auto SortObject() const && -> void {}

        auto SortObject() & -> view::SortView<RangedArrayLike> {
            return {static_cast<RangedArrayLike&>(*this)};
        }

        auto SortObject() const & -> view::SortView<RangedArrayLike const> {
            return {static_cast<RangedArrayLike const&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_SORTVIEWFACTORY_H
