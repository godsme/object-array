//
// Created by Darwin Yuan on 2021/7/6.
//

#ifndef OBJECT_ARRAY_DYNAMICMEM_H
#define OBJECT_ARRAY_DYNAMICMEM_H

#include <l0-infra/array/detail/DynamicArrayMixins.h>

namespace detail {
    template<typename MEM_ALLOCATOR, typename OBJ, std::size_t MAX_NUM>
    struct MemAllocatorAdapter {
        using ObjectType = OBJ;
        using SizeType = DeduceSizeType_t<MAX_NUM>;

    private:
        template<typename ... ARGS>
        auto construct(void* p, ARGS&& ... args) -> OBJ* {
            if constexpr(std::is_aggregate_v<OBJ>) {
                return new (p) OBJ{std::forward<ARGS>(args)...};
            } else {
                return new (p) OBJ(std::forward<ARGS>(args)...);
            }
        }
    public:
        MemAllocatorAdapter(MEM_ALLOCATOR& allocator) : allocator{allocator} {}

        template<typename ... ARGS>
        auto Append(ARGS&& ... args) -> OBJ* {
            auto* p = allocator.AllocMem(sizeof(ObjectType));
            return (p == nullptr) ? nullptr : construct(p, std::forward<ARGS>(args)...);
        }

        auto Remove(OBJ const* p) -> void {
            if(p == nullptr) return;
            p->~OBJ();
            allocator.FreeMem(reinterpret_cast<void*>(const_cast<OBJ*>(p)));
        }

        template<typename ... ARGS>
        auto ReplaceObj(OBJ const* p, ARGS&& ... args) -> OBJ* {
            if(p == nullptr) return p;
            p->~OBJ();
            return construct(reinterpret_cast<void*>(const_cast<OBJ*>(p)), std::forward<ARGS>(args)...);
        }

        auto HasEnoughSlots(SizeType num) const -> bool {
            return true;
        }

    private:
        MEM_ALLOCATOR& allocator;
    };

    struct GlobalMemAllocator {
        auto AllocMem(std::size_t size) -> void* {
            return ::malloc(size);
        }

        auto FreeMem(void* p) -> void {
            return ::free(p);
        }
    };

    template<typename ALLOCATOR, typename POINTER_ARRAY, bool FREE_ON_DTOR = true, typename Allocator = MemAllocatorAdapter<ALLOCATOR, std::remove_pointer_t<typename POINTER_ARRAY::ObjectType>, POINTER_ARRAY::MAX_SIZE>>
    struct GenericMemAllocArray : private Allocator, DynamicArray<Allocator, POINTER_ARRAY, FREE_ON_DTOR> {
        using Parent = DynamicArray<Allocator, POINTER_ARRAY, FREE_ON_DTOR>;

        template<typename ... ARGS>
        GenericMemAllocArray(ALLOCATOR& memAllocator, ARGS&& ... args)
                : Allocator{memAllocator}
                , Parent{*static_cast<Allocator*>(this), std::forward<ARGS>(args)...} {}

        using Parent::Append;
        using Parent::Remove;
        using Parent::ReplaceObj;
        using Parent::HasEnoughSlots;
    };
}

#endif //OBJECT_ARRAY_DYNAMICMEM_H
