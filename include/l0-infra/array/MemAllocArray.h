//
// Created by Darwin Yuan on 2021/7/6.
//

#ifndef OBJECT_ARRAY_MEMALLOCARRAY_H
#define OBJECT_ARRAY_MEMALLOCARRAY_H

#include <l0-infra/array/ObjectArray.h>
#include <l0-infra/array/detail/GenericMemAllocArray.h>

namespace detail {
    template<typename ALLOCATOR, typename OBJ, std::size_t MAX_NUM, bool FREE_ON_DTOR>
    using MemAllocArray = detail::GenericMemAllocArray<ALLOCATOR, ObjectArray<OBJ*, MAX_NUM>, FREE_ON_DTOR>;
}

template<typename ALLOCATOR, typename OBJ, std::size_t MAX_NUM, bool FREE_ON_DTOR = true, typename Parent = detail::MemAllocArray<ALLOCATOR, OBJ, MAX_NUM, FREE_ON_DTOR>>
struct MemAllocArray : Parent {
    MemAllocArray(ALLOCATOR& allocator) : Parent(allocator) {}
};

template<typename OBJ, std::size_t MAX_NUM, bool FREE_ON_DTOR = true, typename Parent = MemAllocArray<detail::GlobalMemAllocator, OBJ, MAX_NUM, FREE_ON_DTOR>>
struct GlobalMemAllocArray : private detail::GlobalMemAllocator, Parent {
    GlobalMemAllocArray() : Parent(*static_cast<detail::GlobalMemAllocator*>(this)) {}
};

#endif //OBJECT_ARRAY_MEMALLOCARRAY_H
