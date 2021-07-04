//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDARRAYVIEW_H
#define OBJECT_ARRAY_INDEXEDARRAYVIEW_H

#include <l0-infra/array/holder/ProxyRangedViewDataHolder.h>
#include <l0-infra/array/mixin/array_like/RangedArrayLike.h>
#include <l0-infra/array/mixin/iterable/IterableWithIndexScopedArrayLike.h>
#include <l0-infra/array/mixin/detail/___public_mixin_delimiter___.h>

namespace view::detail {
    template<template<typename> typename ITERATOR, template<typename, bool> typename REF_HOLDER, template<typename, bool> typename VALUE_HOLDER>
    struct IndexedArrayView {
        using Mixins = mixin::Mixins<
                mixin::RangedArrayLike,
                mixin::___public_mixin_delimiter___,
                ITERATOR>;

        template<typename HOLDER>
        using View = typename Mixins::template Compose<HOLDER>;

        template<typename ARRAY, bool ORDERED>
        using RefView = View<REF_HOLDER<ARRAY, ORDERED>>;

        template<typename ARRAY, bool ORDERED>
        using ValueView = View<VALUE_HOLDER<ARRAY, ORDERED>>;
    };
}

#endif //OBJECT_ARRAY_INDEXEDARRAYVIEW_H
