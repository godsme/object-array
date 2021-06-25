//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_CONTINOUSREADONLYARRAY_H
#define OBJECT_ARRAY_CONTINOUSREADONLYARRAY_H

#include <object-array/detail/ReadOnlyArrayLike.h>

namespace detail {
    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
    class ContinuousReadOnlyArray : public detail::ReadOnlyArrayLike<DATA_HOLDER, MIXINS, ORDERED> {
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
    };
}

#endif //OBJECT_ARRAY_CONTINOUSREADONLYARRAY_H
