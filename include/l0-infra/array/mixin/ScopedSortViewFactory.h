//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SCOPEDSORTVIEWFACTORY_H
#define OBJECT_ARRAY_SCOPEDSORTVIEWFACTORY_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/view/SortView.h>
#include <l0-infra/array/mixin/detail/ValueRangedArray.h>

namespace mixin {
    template<__cOnCePt(SimpleScopedRangedArrayLike) T>
    struct ScopedSortViewFactory : T {
        using Self = T;

        using typename T::RangedArrayLike;
        using typename T::DataHolder;

        using T::GetScope;

    private:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    public:
        auto SortObject() && -> view::ValueSortView<Array> {
            return {reinterpret_cast<Array&&>(*this), GetScope()};
        }

        auto SortObject() const && -> view::ValueSortView<Array const> {
            return {reinterpret_cast<Array const&&>(*this), GetScope()};
        }

        auto SortObject() & -> view::SortView<RangedArrayLike> {
            return {static_cast<RangedArrayLike&>(*this), GetScope()};
        }

        auto SortObject() const & -> view::SortView<RangedArrayLike const> {
            return {static_cast<RangedArrayLike const&>(*this), GetScope()};
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSORTVIEWFACTORY_H
