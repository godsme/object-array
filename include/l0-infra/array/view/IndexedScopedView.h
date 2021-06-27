//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H
#define OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H

#include <l0-infra/array/holder/ScopedViewDataHolder.h>
#include <l0-infra/array/view/detail/IndexedArrayView.h>
#include <l0-infra/array/mixin/IterableIndexedArrayLike.h>

namespace view {
    using IndexedScopedView = typename detail::IndexedArrayView<
            mixin::IterableIndexedScopedArrayLike,
            holder::RefScopedViewDataHolder,
            holder::ValueScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H