//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDARRAYVIEW_H
#define OBJECT_ARRAY_INDEXEDARRAYVIEW_H

#include <object-array/holder/IndexedViewDataHolder.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/IterableIndexedScopedArrayLike.h>

namespace view::detail {
    template<template<typename> typename ITERATOR, template<typename> typename REF_HOLDER, template<typename> typename VALUE_HOLDER>
    struct IndexedArrayView {
        template<typename HOLDER>
        using Mixins = mixin::Combinator<
                HOLDER,
                mixin::RangedArrayLike,
                ITERATOR>;

        template<typename HOLDER>
        class View : ::detail::ArrayComposer<HOLDER, Mixins> {
            using Parent = ::detail::ArrayComposer<HOLDER, Mixins>;
            using Mixins = typename Parent::Mixins;
        public:
            using Parent::Parent;

            using Mixins::begin;
            using Mixins::end;
        };

        template<typename ARRAY>
        using RefView = View<REF_HOLDER<ARRAY>>;

        template<typename ARRAY>
        using ValueView = View<VALUE_HOLDER<ARRAY>>;
    };
}

#endif //OBJECT_ARRAY_INDEXEDARRAYVIEW_H
