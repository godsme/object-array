//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAY_H
#define OBJECT_ARRAY_DYNAMICARRAY_H

#include <l0-infra/array/ObjectArray.h>
#include <l0-infra/array/detail/DynamicArrayMixins.h>

namespace detail {
    template<__cOnCePt(DynamicAllocator) ALLOCATOR, std::size_t MAX_NUM>
    using DynamicArrayBase = detail::DynamicArray<ALLOCATOR, ObjectArray<typename ALLOCATOR::ObjectType*, MAX_NUM>>;
}

template<__cOnCePt(DynamicAllocator) ALLOCATOR, std::size_t MAX_NUM>
struct DynamicArray : detail::DynamicArrayBase<ALLOCATOR, MAX_NUM> {
    using Parent = detail::DynamicArrayBase<ALLOCATOR, MAX_NUM>;
    DynamicArray(ALLOCATOR& allocator) : Parent(allocator) {}
};

#endif //OBJECT_ARRAY_DYNAMICARRAY_H
