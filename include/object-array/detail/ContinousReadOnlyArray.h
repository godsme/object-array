//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_CONTINOUSREADONLYARRAY_H
#define OBJECT_ARRAY_CONTINOUSREADONLYARRAY_H

#include <object-array/detail/ReadOnlyArrayLike.h>

namespace detail {
    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
    class ContinuousReadOnlyArray : public detail::ReadOnlyArrayLike<DATA_HOLDER, MIXINS> {
        using Parent = detail::ReadOnlyArrayLike<DATA_HOLDER, MIXINS>;

    protected:
        using typename Parent::Mixins;

    public:
        using Parent::Parent;

        using Mixins::GetNum;
        using Mixins::Slice;
        using Mixins::From;
        using Mixins::Until;

        using Mixins::Scope;
        using Mixins::Exclude;

    public:
        auto operator==(ContinuousReadOnlyArray const &rhs) const -> bool {
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

        auto operator!=(ContinuousReadOnlyArray const &rhs) const -> bool {
            return !operator==(rhs);
        }
    };
}

#endif //OBJECT_ARRAY_CONTINOUSREADONLYARRAY_H
