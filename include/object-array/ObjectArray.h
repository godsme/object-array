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

    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = detail::ContinuousReadOnlyArray<holder::ObjectArrayDataHolder<T, MAX_NUM>, ObjectArrayMixins>;
}

template<typename T, std::size_t MAX_NUM>
class ObjectArray : public detail::ObjectArray<T, MAX_NUM> {
    using Parent = detail::ObjectArray<T, MAX_NUM>;
    using Mixins = typename Parent::Mixins;
    using DataHolder = typename Parent::DataHolder;
public:
    using BitMap = typename Mixins::BitMap;

public:
    using Parent::Parent;

    using Mixins::Append;
    using Mixins::Replace;
    using Mixins::Erase;
    //using Mixins::Clear;
    using DataHolder::Clear;
    using DataHolder::ClearFrom;
    //using Mixins::ClearUntil;
    using Mixins::CleanUpBy;
    using Mixins::ReplaceObj;
    using Mixins::Remove;
    using Mixins::RemoveBy;
    using Mixins::CleanUp;
    using Mixins::CleanUpEx;
    using Mixins::FindOrAppend;
};

#endif //OBJECT_ARRAY_OBJECTARRAY_H
