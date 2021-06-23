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
        using RangedArrayLike = typename T::RangedArrayLike;
    public:
        auto WithIndex() & -> auto {
            return view::IndexedView::RefView<RangedArrayLike>{reinterpret_cast<RangedArrayLike&>(*this)};
        }
        auto WithIndex() const & -> auto {
            return view::IndexedView::RefView<RangedArrayLike const>{reinterpret_cast<RangedArrayLike const&>(*this)};
        }

        // R-Value WithIndex is not allowed.
        auto WithIndex() && -> void {}
        auto WithIndex() const && -> void {}
    };
}

#endif //OBJECT_ARRAY_INDEXEDVIEWFACTORY_H
