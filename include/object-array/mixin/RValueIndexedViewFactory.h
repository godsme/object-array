//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RVALUEINDEXEDVIEWFACTORY_H
#define OBJECT_ARRAY_RVALUEINDEXEDVIEWFACTORY_H

#include <object-array/mixin/IndexedViewFactory.h>
#include <object-array/concept/RangedArrayLike.h>
#include <object-array/view/IndexedView.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    class RValueIndexedViewFactory : public IndexedViewFactory<T> {
        using Self = IndexedViewFactory<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using RangedArrayLike = typename T::RangedArrayLike;
        using DataHolder = typename T::DataHolder;

    private:
        struct Array : private DataHolder, RangedArrayLike {
            using DataHolder::DataHolder;
            using RangedArrayLike::GetObj;
            using RangedArrayLike::IndexBegin;
            using RangedArrayLike::IndexEnd;

            using SizeType = typename DataHolder::SizeType;
            using ObjectType = typename DataHolder::ObjectType;
            using ElemType = typename DataHolder::ElemType;
            using BitMap = typename RangedArrayLike::BitMap;
            //using Maybe = typename DataHolder::Maybe;

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
