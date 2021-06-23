//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEW_H
#define OBJECT_ARRAY_SCOPEDVIEW_H

#include <object-array/holder/ScopedViewDataHolder.h>
#include <object-array/mixin/detail/Combinator.h>
#include <object-array/mixin/ScopedSimpleFind.h>
#include <object-array/mixin/ScopedRangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/IndexedScopedViewFactory.h>

namespace view::detail {
    template<typename HOLDER>
    using ScopedMixin = mixin::Combinator<
            HOLDER,
            mixin::RangedArrayLike,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt>;

    template<typename HOLDER>
    class ScopedView : ::detail::ArrayComposer<HOLDER, ScopedMixin> {
        using Parent = ::detail::ArrayComposer<HOLDER, ScopedMixin>;
        using Holder = typename Parent::Holder;
        using Mixins = typename Parent::Mixins;

    public:
        using Parent::Parent;

        using Mixins::Find;
        using Mixins::FindIndex;
    };
}

namespace view {
    template<typename ARRAY>
    using ScopedView = detail::ScopedView<holder::RefScopedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using ValueScopedView = detail::ScopedView<holder::ValueScopedViewDataHolder<ARRAY>>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEW_H
