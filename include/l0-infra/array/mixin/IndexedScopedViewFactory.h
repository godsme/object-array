//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/view/IndexedScopedView.h>

namespace mixin {
    template<__cOnCePt(SimpleScopedRangedArrayLike) T>
    class IndexedScopedViewFactory : public T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::RangedArrayLike;
        using typename T::DataHolder;

        using Self::GetScope;

    private:
        struct Array : private DataHolder, RangedArrayLike {
            using DataHolder::DataHolder;
            using RangedArrayLike::IndexBegin;
            using RangedArrayLike::IndexEnd;
            //using RangedArrayLike::GetScope;
            using RangedArrayLike::GetObj;

            using typename DataHolder::SizeType;
            using typename DataHolder::ObjectType;
            using typename RangedArrayLike::BitMap;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;

            Array(Array&&) = default;
        };

    public:
        auto WithIndex() && -> view::IndexedScopedView::ValueView<Array> {
            return {reinterpret_cast<Array&&>(*this), GetScope()};
        }
        auto WithIndex() const&& -> view::IndexedScopedView::ValueView<Array const> {
            return {reinterpret_cast<Array const&&>(*this), GetScope()};
        }
        auto WithIndex() & -> view::IndexedScopedView::RefView<RangedArrayLike> {
            return {reinterpret_cast<RangedArrayLike&>(*this), GetScope()};
        }
        auto WithIndex() const& -> view::IndexedScopedView::RefView<RangedArrayLike const> {
            return {reinterpret_cast<RangedArrayLike const&>(*this), GetScope()};
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
