//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SIMPLEREADONLYARRAYLIKE_H
#define OBJECT_ARRAY_SIMPLEREADONLYARRAYLIKE_H

#include <l0-infra/array/detail/ArrayComposer.h>

namespace detail {
    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
    class SimpleReadOnlyArrayLike : public detail::ArrayComposer<DATA_HOLDER, MIXINS> {
        using Parent = detail::ArrayComposer<DATA_HOLDER, MIXINS>;

    protected:
        using typename Parent::Mixins;
        using typename Parent::Holder;

    public:
        using typename Mixins::BitMap;
        using typename Mixins::SizeType;
        constexpr static SizeType MAX_SIZE = Mixins::MAX_SIZE;

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

    public:
        auto operator==(SimpleReadOnlyArrayLike const &rhs) const -> bool {
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

        auto operator!=(SimpleReadOnlyArrayLike const &rhs) const -> bool {
            return !operator==(rhs);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEREADONLYARRAYLIKE_H
