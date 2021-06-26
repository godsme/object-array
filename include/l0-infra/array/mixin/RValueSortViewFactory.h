//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_RVALUESORTVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUESORTVIEWFACTORY_H

#include <l0-infra/array/mixin/SortViewFactory.h>
#include <l0-infra/array/mixin/detail/ValueRangedArray.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct RValueSortViewFactory : SortViewFactory<T> {
        using Self = SortViewFactory<T>;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::RangedArrayLike;
        using typename T::DataHolder;

    private:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    public:
        using Self::SortObject;

        auto SortObject() && -> view::ValueSortView<Array> {
            return {reinterpret_cast<Array&&>(*this)};
        }

        auto SortObject() const && -> view::ValueSortView<Array const> {
            return {reinterpret_cast<Array const&&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_RVALUESORTVIEWFACTORY_H
