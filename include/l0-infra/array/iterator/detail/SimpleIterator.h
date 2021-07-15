//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_B01151BCD3C945CB8A2FAFD51F94D588
#define OBJECT_ARRAY_2_B01151BCD3C945CB8A2FAFD51F94D588

#include <l0-infra/array/iterator/detail/PointerIterator.h>

namespace iterator::detail {
    template<typename T>
    struct SimpleIterator : PointerIterator<T> {
        using Parent = PointerIterator<T>;
        using Parent::Parent;

        auto operator*() -> T & { return Parent::GetValue(); }
    };
}

#endif //OBJECT_ARRAY_2_B01151BCD3C945CB8A2FAFD51F94D588
