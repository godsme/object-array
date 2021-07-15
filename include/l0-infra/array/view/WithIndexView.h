//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_417C5173E11142FD8EC7D6448CE0EAE7
#define OBJECT_ARRAY_2_417C5173E11142FD8EC7D6448CE0EAE7

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/access/ViewedRange.h>
#include <l0-infra/array/mixin/iterable/IterableWithIndexArrayLike.h>
#include <l0-infra/array/mixin/iterable/IterableWithIndexSortView.h>

namespace with_index_view {
    using Private = ::mixin::Private<
            mixin::ViewedArray,
            mixin::ViewedRange>;

    template<template<typename> typename ITERABLE>
    using Public = mixin::Public<ITERABLE>;

    template<typename HOLDER, template<typename> typename ITERABLE>
    class Array : public Public<ITERABLE>::template Compose<HOLDER, Private, Array<HOLDER, ITERABLE>> {
        using Parent = typename Public<ITERABLE>::template Compose<HOLDER, Private, Array<HOLDER, ITERABLE>>;

    public:
        using Parent::Parent;
    };

    template<template<typename> typename ITERABLE>
    struct WithIndexView {
        template<typename ARRAY>
        using ValueView = Array<typename holder::View<ARRAY>::ValueView, ITERABLE>;
        template<typename ARRAY>
        using RefView = Array<typename holder::View<ARRAY>::RefView, ITERABLE>;
    };
}

using WithIndexView = with_index_view::WithIndexView<mixin::IterableWithIndexArrayLike>;
using SortViewWithIndexView = with_index_view::WithIndexView<mixin::IterableWithIndexSortView>;

#endif //OBJECT_ARRAY_2_417C5173E11142FD8EC7D6448CE0EAE7
