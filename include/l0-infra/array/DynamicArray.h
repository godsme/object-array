//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAY_H
#define OBJECT_ARRAY_DYNAMICARRAY_H

#include <l0-infra/array/ObjectArray.h>
#include <l0-infra/array/detail/DynamicArrayMixins.h>

namespace detail {
    template<__cOnCePt(DynamicAllocator) ALLOCATOR, std::size_t MAX_NUM, bool FREE_ON_DTOR>
    using DynamicArrayBase = detail::DynamicArray<ALLOCATOR, ObjectArray<typename ALLOCATOR::ObjectType*, MAX_NUM>, FREE_ON_DTOR>;
}

template<__cOnCePt(DynamicAllocator) ALLOCATOR, std::size_t MAX_NUM, bool FREE_ON_DTOR = true, typename Parent = detail::DynamicArrayBase<ALLOCATOR, MAX_NUM, FREE_ON_DTOR>>
struct DynamicArray : Parent {
    DynamicArray(ALLOCATOR& allocator) : Parent(allocator) {}
};

#endif //OBJECT_ARRAY_DYNAMICARRAY_H
