//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
#define OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/view/IndexedScopedView.h>

namespace mixin {
    template<_concept::SimpleScopedRangedArrayLike T>
    class IndexedScopedViewFactory : public detail::Extends<T> {
        using Self = detail::Extends<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using ScopedRangedArrayLike = typename T::ScopedRangedArrayLike;
        using DataHolder = typename T::DataHolder;

    private:
        struct Array : private DataHolder, ScopedRangedArrayLike {
            using DataHolder::DataHolder;
            using ScopedRangedArrayLike::IndexBegin;
            using ScopedRangedArrayLike::IndexEnd;
            using ScopedRangedArrayLike::GetScope;

            using SizeType = typename DataHolder::SizeType;
            using ObjectType = typename DataHolder::ObjectType;
            using ElemType = typename DataHolder::ElemType;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;
            Array(Array&&) = default;
        };

    public:
        auto WithIndex() && -> auto {
            return view::IndexedScopedView::ValueView<Array>{reinterpret_cast<Array&&>(*this)};
        }

        auto WithIndex() & -> auto {
            return view::IndexedScopedView::RefView<ScopedRangedArrayLike>{reinterpret_cast<ScopedRangedArrayLike&&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDSCOPEDVIEWFACTORY_H
