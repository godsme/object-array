//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDARRAYVIEW_H
#define OBJECT_ARRAY_INDEXEDARRAYVIEW_H

#include <l0-infra/array/holder/IndexedViewDataHolder.h>
#include <l0-infra/array/detail/ArrayComposer.h>
#include <l0-infra/array/mixin/RangedArrayLike.h>
#include <l0-infra/array/mixin/IterableIndexedScopedArrayLike.h>

namespace view::detail {
    template<template<typename> typename ITERATOR, template<typename, typename> typename REF_HOLDER, template<typename, typename> typename VALUE_HOLDER>
    struct IndexedArrayView {
        using Mixins = mixin::Mixins<
                mixin::RangedArrayLike,
                ITERATOR>;

        template<typename HOLDER>
        class View : ::detail::ArrayComposer<HOLDER, Mixins> {
            using Parent = ::detail::ArrayComposer<HOLDER, Mixins>;
            using typename Parent::Mixins;
        public:
            using Parent::Parent;

            using Mixins::begin;
            using Mixins::end;
        };

        template<typename ARRAY>
        struct RefView : View<REF_HOLDER<ARRAY, RefView<ARRAY>>> {
            using Parent = View<REF_HOLDER<ARRAY, RefView<ARRAY>>>;
            using Parent::Parent;
        };

        template<typename ARRAY>
        struct ValueView : View<VALUE_HOLDER<ARRAY, ValueView<ARRAY>>> {
            using Parent = View<VALUE_HOLDER<ARRAY, ValueView<ARRAY>>>;
            using Parent::Parent;
        };
    };
}

#endif //OBJECT_ARRAY_INDEXEDARRAYVIEW_H
