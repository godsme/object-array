//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_READONLYARRAYLIKE_H
#define OBJECT_ARRAY_READONLYARRAYLIKE_H

#include <l0-infra/array/detail/SimpleReadOnlyArrayLike.h>

namespace detail {
    template<typename DATA_HOLDER, typename MIXINS, bool ORDERED=false>
    class ReadOnlyArrayLike : public SimpleReadOnlyArrayLike<DATA_HOLDER, MIXINS, ORDERED> {
        using Parent = SimpleReadOnlyArrayLike<DATA_HOLDER, MIXINS, ORDERED>;

    protected:
        using typename Parent::Mixins;
        using typename Parent::Holder;

    public:
        using Parent::Parent;

        using Mixins::MinElem;
        using Mixins::MinElemIndex;
        using Mixins::MaxElem;
        using Mixins::MaxElemIndex;
    };
}

#endif //OBJECT_ARRAY_READONLYARRAYLIKE_H
