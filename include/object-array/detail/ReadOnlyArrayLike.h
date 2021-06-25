//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_READONLYARRAYLIKE_H
#define OBJECT_ARRAY_READONLYARRAYLIKE_H

#include <object-array/detail/ArrayComposer.h>

namespace detail {
    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
    class ReadOnlyArrayLike : public detail::ArrayComposer<DATA_HOLDER, MIXINS> {
        using Parent = detail::ArrayComposer<DATA_HOLDER, MIXINS>;

    protected:
        using typename Parent::Mixins;
        using typename Parent::Holder;

    public:
        using typename Mixins::BitMap;

    public:
        using Parent::Parent;

        using Mixins::operator[];
        using Mixins::At;
        using Mixins::First;
        using Mixins::Last;

        using Mixins::begin;
        using Mixins::end;

        using Mixins::GetNum;
        using Mixins::Any;
        using Mixins::None;
        using Mixins::All;
        using Mixins::GetOccupied;
        using Mixins::GetAvailable;
        using Mixins::IsPresent;

        using Mixins::ForEach;

        using Mixins::Find;
        using Mixins::FindIndex;
        using Mixins::Exists;

        using Mixins::MinElem;
        using Mixins::MinElemIndex;
        using Mixins::MaxElem;
        using Mixins::MaxElemIndex;

        using Mixins::WithIndex;

    public:
        auto operator==(ReadOnlyArrayLike const &rhs) const -> bool {
            if (GetNum() != rhs.GetNum()) return false;

            for (auto i = 0; i < GetNum(); i++) {
                if constexpr(ORDERED) {
                    if ((*this)[i] != rhs[i]) return false;
                } else {
                    if (!rhs.Exists((*this)[i])) return false;
                }
            }
            return true;
        }

        auto operator!=(ReadOnlyArrayLike const &rhs) const -> bool {
            return !operator==(rhs);
        }
    };


}

#endif //OBJECT_ARRAY_READONLYARRAYLIKE_H
