//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H
#define OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H

#include <object-array/holder/ScopedViewDataHolder.h>
#include <object-array/view/detail/IndexedArrayView.h>
#include <object-array/mixin/IterableIndexedArrayLike.h>

namespace view {
    using IndexedScopedView = typename detail::IndexedArrayView<mixin::IteratableIndexedScopedArrayLike, holder::RefScopedViewDataHolder, holder::ValueScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H
