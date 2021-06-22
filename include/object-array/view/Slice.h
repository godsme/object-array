//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SLICE_H
#define OBJECT_ARRAY_SLICE_H

#include <object-array/holder/RangedViewDataHolder.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/detail/Combinator.h>

namespace view {
    namespace detail {
        template<typename HOLDER>
        using SliceMixin = mixin::Combinator<
                HOLDER,
                mixin::RangedArrayLike,
                mixin::NonScopedSimpleFind,
                mixin::SimpleFindExt>;

        template<typename ARRAY>
        using Slice = SliceMixin<holder::RangedViewDataHolder<ARRAY>>;
    }

    template<typename ARRAY>
    struct Slice : detail::Slice<ARRAY> {
        using Parent = detail::Slice<ARRAY>;
        using Parent::Parent;
        using Holder = typename Parent::Holder;
    };
}

#endif //OBJECT_ARRAY_SLICE_H
