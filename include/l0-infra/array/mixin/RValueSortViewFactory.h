//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_RVALUESORTVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUESORTVIEWFACTORY_H

#include <l0-infra/array/mixin/SortViewFactory.h>

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
        struct Array : private DataHolder, RangedArrayLike {
            using DataHolder::DataHolder;
            using RangedArrayLike::GetObj;
            using RangedArrayLike::IndexBegin;
            using RangedArrayLike::IndexEnd;

            using typename DataHolder::SizeType;
            using typename DataHolder::ObjectType;
            using typename DataHolder::ElemType;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;
            Array(Array&&) = default;
        };

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
