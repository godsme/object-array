//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H
#define OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H

#include <l0-infra/array/view/detail/IndexedArrayView.h>
#include <l0-infra/array/mixin/iterable/IterableWithIndexArrayLike.h>
#include <l0-infra/array/holder/ProxyScopedViewDataHolder.h>

namespace view {
    using IndexedScopedView = typename detail::IndexedArrayView<
            mixin::IterableWithIndexScopedArrayLike,
            holder::RefProxyScopedViewDataHolder,
            holder::ValueProxyScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_INDEXEDSCOPEDVIEW_H
