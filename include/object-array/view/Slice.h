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

    template<typename ARRAY, typename Parent = detail::Slice<ARRAY>>
    class Slice : Parent {
        using Holder = typename Parent::Holder;
        using Mixins = typename Parent::Mixins;

    public:
        using Parent::Parent;

        using Mixins::Find;
        using Mixins::FindIndex;
    };
}

#endif //OBJECT_ARRAY_SLICE_H
