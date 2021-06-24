//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/view/IndexedScopedView.h>

namespace mixin {
    template<_concept::SimpleScopedRangedArrayLike T>
    class IndexedScopedViewFactory : public T {
        using Self = T;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using ScopedRangedArrayLike = typename T::ScopedRangedArrayLike;
        using DataHolder = typename T::DataHolder;
        using Self::GetScope;

    private:
        struct Array : private DataHolder, ScopedRangedArrayLike {
            using DataHolder::DataHolder;
            using ScopedRangedArrayLike::IndexBegin;
            using ScopedRangedArrayLike::IndexEnd;
            using ScopedRangedArrayLike::GetScope;
            using ScopedRangedArrayLike::GetObj;

            using SizeType = typename DataHolder::SizeType;
            using ObjectType = typename DataHolder::ObjectType;
            using BitMap = typename ScopedRangedArrayLike::BitMap;

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
        auto WithIndex() & -> view::IndexedScopedView::RefView<ScopedRangedArrayLike> {
            return {reinterpret_cast<ScopedRangedArrayLike&>(*this), GetScope()};
        }
        auto WithIndex() const& -> view::IndexedScopedView::RefView<ScopedRangedArrayLike const> {
            return {reinterpret_cast<ScopedRangedArrayLike const&>(*this), GetScope()};
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
