//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUEWITHINDEXVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUEWITHINDEXVIEWFACTORY_H

#include <l0-infra/array/mixin/factory/WithIndexViewFactory.h>
#include <l0-infra/array/mixin/detail/ValueRangedArray.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/view/WithIndexView.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class RValueWithIndexViewFactory : public WithIndexViewFactory<T> {
        using Self = WithIndexViewFactory<T>;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
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

#endif //OBJECT_ARRAY_RVALUEWITHINDEXVIEWFACTORY_H
