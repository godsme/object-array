//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUEINDEXEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUEINDEXEDVIEWFACTORY_H

#include <l0-infra/array/mixin/IndexedViewFactory.h>
#include <l0-infra/array/mixin/detail/ValueRangedArray.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/IndexedView.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class RValueIndexedViewFactory : public IndexedViewFactory<T> {
        using Self = IndexedViewFactory<T>;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::RangedArrayLike;
        using typename T::DataHolder;

    private:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    public:
        using Self::WithIndex;

        auto WithIndex() && -> view::IndexedView::ValueView<Array> {
            return {reinterpret_cast<Array&&>(*this)};
        }

        auto WithIndex() const && -> view::IndexedView::ValueView<Array const> {
            return {reinterpret_cast<Array const&&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_RVALUEINDEXEDVIEWFACTORY_H
