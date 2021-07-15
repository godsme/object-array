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

namespace with_index_scope_view {
    using Private = ::mixin::Private<
            mixin::ViewedArray,
            mixin::ViewedScope>;

    using Public = mixin::Public<
            mixin::IterableWithIndexScopedArrayLike>;

    template<typename HOLDER>
    class Array : public Public::Compose<HOLDER, Private, Array<HOLDER>> {
        using Parent = Public::Compose<HOLDER, Private, Array<HOLDER>>;

    public:
        using Parent::Parent;
    };
}

template<typename ARRAY>
using ValueWithIndexScopeView = with_index_scope_view::Array<typename holder::View<ARRAY>::ValueView>;

template<typename ARRAY>
using RefWithIndexScopeView = with_index_scope_view::Array<typename holder::View<ARRAY>::RefView>;

#endif //OBJECT_ARRAY_2_76176F0D70B54BEF94BA01B5DC88718D
