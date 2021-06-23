//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDVIEW_H
#define OBJECT_ARRAY_INDEXEDVIEW_H

#include <object-array/holder/IndexedViewDataHolder.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/IteratableIndexedArrayLike.h>

namespace view::detail {
    template<typename HOLDER>
    using WithIndexMixin = mixin::Combinator<
            HOLDER,
            mixin::RangedArrayLike,
            mixin::IteratableIndexedArrayLike>;

    template<typename HOLDER, typename Parent = WithIndexMixin<HOLDER>>
    class WithIndex : Parent {
        using Mixins = typename Parent::Mixins;
    public:
        using Parent::Parent;

        using Mixins::begin;
        using Mixins::end;
    };
}

namespace view {
    template<typename ARRAY>
    using IndexedView = detail::WithIndex<holder::RefIndexedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using ValueIndexedView = detail::WithIndex<holder::ValueIndexedViewDataHolder<ARRAY>>;
}

#endif //OBJECT_ARRAY_INDEXEDVIEW_H
