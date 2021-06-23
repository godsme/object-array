//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEW_H
#define OBJECT_ARRAY_SCOPEDVIEW_H

#include <object-array/holder/ScopedViewDataHolder.h>
#include <object-array/mixin/detail/Mixins.h>
#include <object-array/mixin/ScopedSimpleFind.h>
#include <object-array/mixin/ScopedRangedArrayLike.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/IndexedScopedViewFactory.h>
#include <object-array/mixin/IterableScopedArrayLike.h>

namespace view::detail {
    using ScopedMixin = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::IterableScopedArrayLike,
            mixin::RValueIndexedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt>;

    template<typename HOLDER>
    class ScopedView : ::detail::ArrayComposer<HOLDER, ScopedMixin> {
        using Parent = ::detail::ArrayComposer<HOLDER, ScopedMixin>;
        using Holder = typename Parent::Holder;
        using Mixins = typename Parent::Mixins;

    public:
        using Parent::Parent;

        using Mixins::begin;
        using Mixins::end;

        using Mixins::Find;
        using Mixins::FindIndex;

        using Mixins::WithIndex;
    };
}

namespace view {
    template<typename ARRAY>
    using ScopedView = detail::ScopedView<holder::RefScopedViewDataHolder<ARRAY>>;

    template<typename ARRAY>
    using ValueScopedView = detail::ScopedView<holder::ValueScopedViewDataHolder<ARRAY>>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEW_H
