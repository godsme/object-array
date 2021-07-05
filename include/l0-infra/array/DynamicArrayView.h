//
// Created by Darwin Yuan on 2021/7/6.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAYVIEW_H
#define OBJECT_ARRAY_DYNAMICARRAYVIEW_H

#include <l0-infra/array/ArrayView.h>
#include <l0-infra/array/detail/DynamicArrayMixins.h>

namespace detail {
    template<__cOnCePt(DynamicAllocator) ALLOCATOR, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
    using DynamicArrayView = detail::DynamicArray<ALLOCATOR, detail::NonConstArrayView<typename ALLOCATOR::ObjectType*, SIZE_TYPE, MAX_NUM>>;
}

template<__cOnCePt(DynamicAllocator) ALLOCATOR, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
struct DynamicArrayView : detail::DynamicArrayView<ALLOCATOR, SIZE_TYPE, MAX_NUM> {
    using Parent = detail::DynamicArrayView<ALLOCATOR, SIZE_TYPE, MAX_NUM>;
    DynamicArrayView(ALLOCATOR& allocator, typename ALLOCATOR::ObjectType* (&p)[MAX_NUM], SIZE_TYPE& num) : Parent(allocator, p, num) {}
};

template<__cOnCePt(DynamicAllocator) ALLOCATOR, typename OBJ, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
DynamicArrayView(ALLOCATOR&, OBJ* (&p)[MAX_NUM], SIZE_TYPE& num) -> DynamicArrayView<ALLOCATOR, SIZE_TYPE, MAX_NUM>;

#endif //OBJECT_ARRAY_DYNAMICARRAYVIEW_H
