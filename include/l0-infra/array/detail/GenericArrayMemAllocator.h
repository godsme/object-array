//
// Created by Darwin Yuan on 2021/7/6.
//

#ifndef OBJECT_ARRAY_DYNAMICMEM_H
#define OBJECT_ARRAY_DYNAMICMEM_H

#include <l0-infra/base/DeduceSizeType.h>
#include <utility>
#include <type_traits>

namespace detail {
    template<typename OBJ, typename MEM_ALLOCATOR>
    struct GenericArrayMemAllocator {
        using ObjectType = OBJ;

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
        GenericArrayMemAllocator(MEM_ALLOCATOR& allocator) : allocator{allocator} {}

        template<typename ... ARGS>
        auto Append(ARGS&& ... args) -> OBJ* {
            auto* p = allocator.AllocMem(sizeof(ObjectType));
            return (p == nullptr) ? nullptr : construct(p, std::forward<ARGS>(args)...);
        }

        auto Remove(OBJ const* p) -> void {
            if(p == nullptr) return;
            if constexpr(!std::is_trivially_destructible_v<OBJ>) {
                p->~OBJ();
            }
            allocator.FreeMem(reinterpret_cast<void*>(const_cast<OBJ*>(p)));
        }

        template<typename ... ARGS>
        auto ReplaceObj(OBJ const* p, ARGS&& ... args) -> OBJ* {
            if(p == nullptr) return p;
            if constexpr(!std::is_trivially_destructible_v<OBJ>) {
                p->~OBJ();
            }
            return construct(reinterpret_cast<void*>(const_cast<OBJ*>(p)), std::forward<ARGS>(args)...);
        }

        auto HasEnoughSlots(std::size_t num) const -> bool {
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
}

#endif //OBJECT_ARRAY_DYNAMICMEM_H
