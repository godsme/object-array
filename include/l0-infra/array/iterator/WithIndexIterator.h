//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_WITHINDEXITERATOR_H
#define OBJECT_ARRAY_WITHINDEXITERATOR_H

#include <l0-infra/array/iterator/Iterator.h>
#include <l0-infra/array/iterator/detail/WithIndexIterator.h>

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE>
    struct WithIndexIterator : detail::WithIndexIterator<ARRAY, OBJ_TYPE> {
        using Parent = detail::WithIndexIterator<ARRAY, OBJ_TYPE>;
        using Parent::Parent;
        auto operator++() -> WithIndexIterator& {
            Parent::StepForward();
            return *this;
        }
    };

    template<typename ARRAY>
    WithIndexIterator(ARRAY&, typename ARRAY::SizeType) ->
        WithIndexIterator<ARRAY,
            std::conditional_t<std::is_const_v<ARRAY>,
                    std::add_const_t<typename ARRAY::ObjectType>,
                            typename ARRAY::ObjectType>>;
}

#endif //OBJECT_ARRAY_WITHINDEXITERATOR_H
