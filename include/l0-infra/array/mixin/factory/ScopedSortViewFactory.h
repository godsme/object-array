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
    class ScopedSortViewFactory : public T {
        using Self = T;

    protected:
        using typename T::ScopedRangedArrayLike;
        using typename T::DataHolder;

    private:
        using Array = detail::ValueScopedRangedArray<DataHolder, ScopedRangedArrayLike>;

    public:
        auto SortObject() && -> view::ValueSortView<Array> {
            return {reinterpret_cast<Array&&>(*this)};
        }

        auto SortObject() const && -> view::ValueSortView<Array const> {
            return {reinterpret_cast<Array const&&>(*this)};
        }

        auto SortObject() & -> view::SortView<ScopedRangedArrayLike> {
            return {static_cast<ScopedRangedArrayLike&>(*this)};
        }

        auto SortObject() const & -> view::SortView<ScopedRangedArrayLike const> {
            return {static_cast<ScopedRangedArrayLike const&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSORTVIEWFACTORY_H
