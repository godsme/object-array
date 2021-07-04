//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_WITHINDEXVIEW_H
#define OBJECT_ARRAY_WITHINDEXVIEW_H

#include <l0-infra/array/holder/ProxyRangedViewDataHolder.h>
#include <l0-infra/array/mixin/array_like/RangedArrayLike.h>
#include <l0-infra/array/view/detail/IndexedArrayView.h>
#include <l0-infra/array/mixin/iterable/IterableWithIndexArrayLike.h>

namespace view {
    using IndexedView = typename detail::IndexedArrayView<
            mixin::IterableWithIndexArrayLike,
            holder::RefProxyRangedViewDataHolder,
            holder::ValueProxyRangedViewDataHolder>;
}

#endif //OBJECT_ARRAY_WITHINDEXVIEW_H
