//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_DETAIL_CONTINUOUSARRAYLIKE_H
#define OBJECT_ARRAY_DETAIL_CONTINUOUSARRAYLIKE_H

#include <object-array/detail/ContinuousReadOnlyArray.h>

namespace detail {
    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
    class ContinuousArrayLike : public detail::ContinuousReadOnlyArray<DATA_HOLDER, MIXINS, ORDERED> {
        using Parent = detail::ContinuousReadOnlyArray<DATA_HOLDER, MIXINS, ORDERED>;

    public:
        using Parent::Parent;
        using Mixins = typename Parent::Mixins;
        using DataHolder = typename Parent::DataHolder;

    public:
        using BitMap = typename Mixins::BitMap;
        using OffsetType = typename Mixins::OffsetType;
        using EndOffsetType = typename Mixins::EndOffsetType;

    public:
        using Mixins::Append;
        using Mixins::Replace;
        using Mixins::Erase;
        using Mixins::CleanUpBy;
        using Mixins::ReplaceObj;
        using Mixins::Remove;
        using Mixins::RemoveBy;
        using Mixins::CleanUp;
        using Mixins::CleanUpEx;
        using Mixins::FindOrAppend;
        using Mixins::ClearFrom;
        using DataHolder::Clear;

        auto Clear(OffsetType from, EndOffsetType until) -> void {
            Mixins::template Clear<ORDERED>(from, until);
        }

        auto ClearUntil(EndOffsetType until) -> void {
            Mixins::template ClearUntil<ORDERED>(until);
        }
    };
}

#endif //OBJECT_ARRAY_DETAIL_CONTINUOUSARRAYLIKE_H
