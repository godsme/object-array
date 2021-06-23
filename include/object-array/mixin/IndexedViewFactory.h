//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDVIEWFACTORY_H
#define OBJECT_ARRAY_INDEXEDVIEWFACTORY_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/RangedArrayLike.h>
#include <object-array/view/IndexedView.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    class IndexedViewFactory : public detail::Extends<T> {
        using Self = detail::Extends<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using RangedArrayLike = typename T::RangedArrayLike;
        using DataHolder = typename T::DataHolder;

        using Self::IndexBegin;
        using Self::IndexEnd;

    private:
        struct Array : private DataHolder, RangedArrayLike {
            using DataHolder::DataHolder;
            using RangedArrayLike::GetObj;
            using RangedArrayLike::IndexBegin;
            using RangedArrayLike::IndexEnd;

            using SizeType = typename DataHolder::SizeType;
            using ObjectType = typename DataHolder::ObjectType;
            using ElemType = typename DataHolder::ElemType;

            constexpr static auto MAX_SIZE = DataHolder::MAX_SIZE;
            Array(Array&&) = default;
        };

    public:
        auto WithIndex() && -> auto {
            return view::IndexedView::ValueView<Array>{reinterpret_cast<Array&&>(*this)};
        }

        auto WithIndex() & -> auto {
            return view::IndexedView::RefView<RangedArrayLike>{reinterpret_cast<RangedArrayLike&&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDVIEWFACTORY_H
