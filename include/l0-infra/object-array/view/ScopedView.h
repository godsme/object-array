//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEW_H
#define OBJECT_ARRAY_SCOPEDVIEW_H

#include <l0-infra/object-array/holder/ScopedViewDataHolder.h>
#include <l0-infra/object-array/mixin/detail/Mixins.h>
#include <l0-infra/object-array/mixin/ScopedSimpleFind.h>
#include <l0-infra/object-array/mixin/SimpleFindExt.h>
#include <l0-infra/object-array/mixin/IndexedScopedViewFactory.h>
#include <l0-infra/object-array/mixin/IterableScopedArrayLike.h>
#include <l0-infra/object-array/mixin/IndexedRefAccessor.h>
#include <l0-infra/object-array/mixin/ScopedByIndexAccessor.h>
#include <l0-infra/object-array/mixin/RangedScopedElemCount.h>

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
        using typename Parent::Mixins;
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
