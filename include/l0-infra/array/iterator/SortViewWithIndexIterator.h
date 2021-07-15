//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_0D5011A46850462EADC75C2D12B0226B
#define OBJECT_ARRAY_2_0D5011A46850462EADC75C2D12B0226B

#include <l0-infra/array/iterator/Iterator.h>
#include <l0-infra/array/iterator/detail/WithIndexIterator.h>
#include <l0-infra/base/detail/CondConst.h>
#include <l0-infra/array/iterator/detail/IndexIterator.h>

namespace iterator {
    template<typename ARRAY, typename OBJ_TYPE>
    struct SortViewWithIndexIterator : detail::ByPointerWithIndexIterator<ARRAY, OBJ_TYPE> {
        using Parent = detail::ByPointerWithIndexIterator<ARRAY, OBJ_TYPE>;
        using Parent::Parent;
        auto operator++() -> SortViewWithIndexIterator& {
            Parent::StepForward();
            return *this;
        }
    };

    template<typename ARRAY>
    SortViewWithIndexIterator(ARRAY&, typename ARRAY::SizeType*) -> SortViewWithIndexIterator<ARRAY, ::detail::CondConst_t<std::is_const_v<ARRAY>, typename ARRAY::ObjectType>>;
}

#endif //OBJECT_ARRAY_2_0D5011A46850462EADC75C2D12B0226B
