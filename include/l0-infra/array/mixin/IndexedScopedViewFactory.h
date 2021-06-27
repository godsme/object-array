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
        using typename T::ScopedRangedArrayLike;
        using typename T::DataHolder;

        using Self::GetScope;

    private:
        struct Array : private DataHolder, ScopedRangedArrayLike {
            using DataHolder::DataHolder;
            using ScopedRangedArrayLike::IndexBegin;
            using ScopedRangedArrayLike::IndexEnd;
            using ScopedRangedArrayLike::GetScope;
            using ScopedRangedArrayLike::GetObj;

            using typename DataHolder::SizeType;
            using typename DataHolder::ObjectType;
            using typename ScopedRangedArrayLike::BitMap;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;

            Array(Array&&) = default;
        };

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
