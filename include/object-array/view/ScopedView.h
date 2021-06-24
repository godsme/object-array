//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEW_H
#define OBJECT_ARRAY_SCOPEDVIEW_H

#include <object-array/holder/ScopedViewDataHolder.h>
#include <object-array/mixin/detail/Mixins.h>
#include <object-array/mixin/ScopedSimpleFind.h>
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/IndexedScopedViewFactory.h>
#include <object-array/mixin/IterableScopedArrayLike.h>
#include <object-array/mixin/IndexedRefAccessor.h>
#include <object-array/mixin/ScopedByIndexAccessor.h>
#include <object-array/mixin/RangedScopedElemCount.h>

namespace view::detail {
    using ScopedMixins = mixin::Mixins<
            mixin::RangedArrayLike,
            mixin::IndexedRefAccessor,
            mixin::ScopedByIndexAccessor,
            mixin::RangedScopedElemCount,
            mixin::IterableScopedArrayLike,
            mixin::IndexedScopedViewFactory,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt>;

    template<typename HOLDER>
    class ScopedView : ::detail::ArrayComposer<HOLDER, ScopedMixins> {
        using Parent = ::detail::ArrayComposer<HOLDER, ScopedMixins>;
        using Mixins = typename Parent::Mixins;
    public:
        using Parent::Parent;

        using Mixins::operator[];
        using Mixins::At;
        using Mixins::First;
        using Mixins::Last;

        using Mixins::begin;
        using Mixins::end;

        using Parent::GetNum;
        using Parent::Any;
        using Parent::None;
        using Parent::All;

        using Mixins::Find;
        using Mixins::FindIndex;
        using Mixins::Exists;

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
