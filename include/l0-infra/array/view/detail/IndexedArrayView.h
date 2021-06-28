//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDARRAYVIEW_H
#define OBJECT_ARRAY_INDEXEDARRAYVIEW_H

#include <l0-infra/array/holder/IndexedViewDataHolder.h>
#include <l0-infra/array/detail/ArrayComposer.h>
#include <l0-infra/array/mixin/RangedArrayLike.h>
#include <l0-infra/array/mixin/IterableIndexedScopedArrayLike.h>
#include <l0-infra/array/mixin/detail/PublicMixinSplitter.h>

namespace view::detail {
    template<template<typename> typename ITERATOR, template<typename> typename REF_HOLDER, template<typename> typename VALUE_HOLDER>
    struct IndexedArrayView {
        using Mixins = mixin::Mixins<
                mixin::RangedArrayLike,
                mixin::detail::PublicMixinSplitter,
                ITERATOR>;

        template<typename HOLDER>
        using View = typename Mixins::template Compose<HOLDER>;

        template<typename ARRAY>
        using RefView = View<REF_HOLDER<ARRAY>>;

        template<typename ARRAY>
        using ValueView = View<VALUE_HOLDER<ARRAY>>;
    };
}

#endif //OBJECT_ARRAY_INDEXEDARRAYVIEW_H
