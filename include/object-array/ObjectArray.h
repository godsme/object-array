//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <object-array/holder/ObjectArrayDataHolder.h>
#include <object-array/detail/ContinuousArrayMixin.h>
#include <object-array/detail/ContinousReadOnlyArray.h>

namespace detail {
    using ObjectArrayMixins =
            detail::ContinuousArrayMixin::Extends<
                mixin::RangedViewFactory,
                mixin::ScopedViewFactory,
                mixin::IndexedViewFactory>;

    template<typename T, std::size_t MAX_NUM, bool ORDERED>
    using ObjectArray = detail::ContinuousReadOnlyArray<holder::ObjectArrayDataHolder<T, MAX_NUM>, ObjectArrayMixins, ORDERED>;
}

template<typename T, std::size_t MAX_NUM, bool ORDERED = false>
class ObjectArray : public detail::ObjectArray<T, MAX_NUM, ORDERED> {
    using Parent = detail::ObjectArray<T, MAX_NUM, ORDERED>;
    using Mixins = typename Parent::Mixins;
    using DataHolder = typename Parent::DataHolder;

public:
    using BitMap = typename Mixins::BitMap;
    using OffsetType = typename Mixins::OffsetType;
    using EndOffsetType = typename Mixins::EndOffsetType;

public:
    using Parent::Parent;

    using Mixins::Append;
    using Mixins::Replace;
    using Mixins::Erase;
    using DataHolder::Clear;
    using Mixins::CleanUpBy;
    using Mixins::ReplaceObj;
    using Mixins::Remove;
    using Mixins::RemoveBy;
    using Mixins::CleanUp;
    using Mixins::CleanUpEx;
    using Mixins::FindOrAppend;

    auto ClearFrom(OffsetType from) {
        DataHolder::ClearFrom(from.ToIndex(Parent::GetNum()));
    }

    auto Clear(OffsetType from, EndOffsetType until) {
        DataHolder::template ClearRange<ORDERED>(from.ToIndex(Parent::GetNum()), until.ToIndex(Parent::GetNum()));
    }

    auto ClearUntil(EndOffsetType until) {
        DataHolder::template ClearRange<ORDERED>(0, until.ToIndex(Parent::GetNum()));
    }
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
