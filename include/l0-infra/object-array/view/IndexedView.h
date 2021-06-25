//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDVIEW_H
#define OBJECT_ARRAY_INDEXEDVIEW_H

#include <l0-infra/object-array/holder/IndexedViewDataHolder.h>
#include <l0-infra/object-array/mixin/RangedArrayLike.h>
#include <l0-infra/object-array/view/detail/IndexedArrayView.h>
#include <l0-infra/object-array/mixin/IterableIndexedArrayLike.h>

namespace view {
    using IndexedView = typename detail::IndexedArrayView<
            mixin::IterableIndexedArrayLike,
            holder::RefIndexedViewDataHolder,
            holder::ValueIndexedViewDataHolder>;
}

#endif //OBJECT_ARRAY_INDEXEDVIEW_H
