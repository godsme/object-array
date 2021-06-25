//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUEINDEXEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUEINDEXEDVIEWFACTORY_H

#include <l0-infra/array/mixin/IndexedViewFactory.h>
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
        struct Array : private DataHolder, RangedArrayLike {
            using DataHolder::DataHolder;
            using RangedArrayLike::GetObj;
            using RangedArrayLike::IndexBegin;
            using RangedArrayLike::IndexEnd;

            using typename DataHolder::SizeType;
            using typename DataHolder::ObjectType;
            using typename DataHolder::ElemType;
            using typename RangedArrayLike::BitMap;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;

            Array(Array&&) = default;
        };

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
