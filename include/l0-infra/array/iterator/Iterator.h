//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_4639216D09764DD6B410A07EBBB09C48
#define OBJECT_ARRAY_2_4639216D09764DD6B410A07EBBB09C48

#include <l0-infra/array/iterator/detail/SimpleIterator.h>

namespace iterator {
    template<typename T>
    struct Iterator : detail::SimpleIterator<T> {
        using Parent = detail::SimpleIterator<T>;
        using Parent::Parent;
        auto operator++() -> Iterator& {
            Parent::StepForward();
            return *this;
        }
    };
}

#endif //OBJECT_ARRAY_2_4639216D09764DD6B410A07EBBB09C48
