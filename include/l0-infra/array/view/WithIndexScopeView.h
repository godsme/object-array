//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_76176F0D70B54BEF94BA01B5DC88718D
#define OBJECT_ARRAY_2_76176F0D70B54BEF94BA01B5DC88718D

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/array_like/ViewedScope.h>
#include <l0-infra/array/mixin/iterable/IterableWithIndexScopeArrayLike.h>
#include <l0-infra/array/mixin/iterable/IterableScopeEnumArrayLike.h>

namespace with_index_scope_view {
    using Private = ::mixin::Private<
            mixin::ViewedArray,
            mixin::ViewedScope>;

    //mixin::IterableWithIndexScopedArrayLike
    template<template<typename> typename ITERABLE>
    using Public = mixin::Public<ITERABLE>;

    template<typename HOLDER, template<typename> typename ITERABLE>
    class Array : public Public<ITERABLE>::template Compose<HOLDER, Private, Array<HOLDER, ITERABLE>> {
        using Parent = typename Public<ITERABLE>::template  Compose<HOLDER, Private, Array<HOLDER, ITERABLE>>;

    public:
        using Parent::Parent;
    };

    template<template<typename> typename ITERABLE>
    struct View {
        template<typename ARRAY>
        using ValueView = Array<typename holder::View<ARRAY>::ValueView, ITERABLE>;
        template<typename ARRAY>
        using RefView = Array<typename holder::View<ARRAY>::RefView, ITERABLE>;
    };
}

using WithIndexScopeView = with_index_scope_view::View<mixin::IterableWithIndexScopedArrayLike>;
using EnumerateScopeView = with_index_scope_view::View<mixin::IterableScopeEnumArrayLike>;

#endif //OBJECT_ARRAY_2_76176F0D70B54BEF94BA01B5DC88718D
