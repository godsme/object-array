//
// Created by Darwin Yuan on 2021/7/6.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAYVIEW_H
#define OBJECT_ARRAY_DYNAMICARRAYVIEW_H

#include <l0-infra/array/ArrayView.h>
#include <l0-infra/array/detail/DynamicArrayLike.h>

namespace detail {
    template<__cOnCePt(DynamicAllocator) ALLOCATOR, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, bool FREE_ON_DTOR>
    using DynamicArrayView = detail::DynamicArrayLike<ALLOCATOR, detail::NonConstArrayView<typename ALLOCATOR::ObjectType*, SIZE_TYPE, MAX_NUM>, FREE_ON_DTOR>;
}

template<__cOnCePt(DynamicAllocator) ALLOCATOR, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, bool FREE_ON_DTOR = false, typename Parent = detail::DynamicArrayView<ALLOCATOR, SIZE_TYPE, MAX_NUM, FREE_ON_DTOR>>
struct DynamicArrayView : Parent {
    DynamicArrayView(ALLOCATOR& allocator, typename ALLOCATOR::ObjectType* (&p)[MAX_NUM], SIZE_TYPE& num) : Parent(allocator, p, num) {}
};

template<__cOnCePt(DynamicAllocator) ALLOCATOR, typename OBJ, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
DynamicArrayView(ALLOCATOR&, OBJ* (&p)[MAX_NUM], SIZE_TYPE& num) -> DynamicArrayView<ALLOCATOR, SIZE_TYPE, MAX_NUM>;

#endif //OBJECT_ARRAY_DYNAMICARRAYVIEW_H
