//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/view/IndexedScopedView.h>
#include <l0-infra/array/mixin/detail/ValueScopedRangedArray.h>

namespace mixin {
    template<__cOnCePt(SimpleScopedRangedArrayLike) T>
    class IndexedScopedViewFactory : public T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::ScopedRangedArrayLike;
        using typename T::DataHolder;

        using Self::GetScope;

    private:
        using Array = detail::ValueScopedRangedArray<DataHolder, ScopedRangedArrayLike>;

    public:
        auto WithIndex() && -> view::IndexedScopedView::ValueView<Array> {
            return {reinterpret_cast<Array&&>(*this)};
        }
        auto WithIndex() const&& -> view::IndexedScopedView::ValueView<Array const> {
            return {reinterpret_cast<Array const&&>(*this)};
        }
        auto WithIndex() & -> view::IndexedScopedView::RefView<ScopedRangedArrayLike> {
            return {reinterpret_cast<ScopedRangedArrayLike&>(*this)};
        }
        auto WithIndex() const& -> view::IndexedScopedView::RefView<ScopedRangedArrayLike const> {
            return {reinterpret_cast<ScopedRangedArrayLike const&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
