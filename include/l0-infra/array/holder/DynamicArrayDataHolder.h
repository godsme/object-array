//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAYDATAHOLDER_H
#define OBJECT_ARRAY_DYNAMICARRAYDATAHOLDER_H

#include <l0-infra/array/concept/DynamicAllocator.h>
#include <l0-infra/array/detail/ArrayIndices.h>
#include <l0-infra/array/ObjectArray.h>

namespace holder::detail {
    template<typename HOLDER>
    class DynamicArrayDataHolderInterface {
        dEcL_tHiS(HOLDER);
    public:
        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        auto GetPointers() const -> decltype(auto) { return (This()->pointers); }
        auto GetPointers() -> decltype(auto) { return (This()->pointers); }
        auto GetObj(SizeType n) -> ObjectType& { return *(This()->pointers[n]); }
        auto GetObj(SizeType n) const -> ObjectType const& { return *(This()->pointers[n]); }
        auto Num() const -> SizeType { return This()->pointers.GetNum(); }

        template<typename ... ARGS>
        auto DoAppend(ARGS&& ... args) -> ObjectType* {
            return This()->DoAppend(std::forward<ARGS>(args)...);
        }

        template<typename ... ARGS>
        auto DoReplace(SizeType n, ARGS&& ... args) -> ObjectType* {
            return This()->DoReplace(n, std::forward<ARGS>(args)...);
        }

        auto DoErase(SizeType n) -> void {
            return This()->DoErase(n);
        }
    };
}

namespace holder {
    template<__cOnCePt(DynamicAllocator) ALLOCATOR, std::size_t MAX_NUM>
    struct DynamicArrayDataHolder {
        using ObjectType = typename ALLOCATOR::ObjectType;
        using PointerArray = ObjectArray<ObjectType*, MAX_NUM>;
        using SizeType = typename PointerArray::SizeType;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        constexpr static bool IS_CONST = false;
        constexpr static bool IS_ORDERED = false;

        using Interface = detail::DynamicArrayDataHolderInterface<DynamicArrayDataHolder>;

    private:
        auto ClearContent() {
            for(auto* pointer : pointers) {
                allocator.Remove(pointer);
            }
        }

        auto DoClear() {
            ClearContent();
            pointers.Clear();
        }

        auto DoErase(SizeType n) -> void {
            if(n < pointers.GetNum()) {
                auto* p = pointers[n];
                allocator.Remove(p);
                pointers.Erase(n);
            }
        }

        auto CopyFrom(DynamicArrayDataHolder const& rhs) {
            if(!allocator.HasEnoughSlots(rhs.pointers.GetNum())) { return; }
            for(auto* pointer : rhs.pointers) {
                auto* p = allocator.Append(*pointer);
                if(p == nullptr) {
                    DoClear();
                    return;
                }
                pointers.Append(p);
            }
        }

        template<typename ... ARGS>
        auto DoAppend(ARGS&& ... args) -> ObjectType* {
            if(pointers.All()) return nullptr;
            auto* p = allocator.Append(std::forward<ARGS>(args)...);
            if(p == nullptr) return nullptr;
            pointers.Append(p);
            return p;
        }

        template<typename ... ARGS>
        auto DoReplace(SizeType n, ARGS&& ... args) -> ObjectType* {
            if(n >= pointers.GetNum()) return nullptr;
            return allocator.ReplaceObj(pointers[n], std::forward<ARGS>(args)...);
        }

    public:
        DynamicArrayDataHolder(ALLOCATOR& allocator) : allocator{allocator} {}

        DynamicArrayDataHolder(DynamicArrayDataHolder const& rhs) : allocator{rhs.allocator} {
            CopyFrom(rhs);
        }

        DynamicArrayDataHolder(DynamicArrayDataHolder&& rhs)
            : allocator{rhs.allocator}
            , pointers(std::move(rhs.pointers)) {
        }

        auto operator=(DynamicArrayDataHolder const& rhs) -> DynamicArrayDataHolder& {
            DoClear();
            if(allocator == rhs.allocator) {
                CopyFrom(rhs);
            }
            return *this;
        }

        auto operator=(DynamicArrayDataHolder&& rhs) -> DynamicArrayDataHolder& {
            DoClear();
            if(allocator == rhs.allocator) {
                pointers = std::move(rhs.pointers);
            }
            return *this;
        }

        ~DynamicArrayDataHolder() {
            ClearContent();
        }

    private:
        template<typename>
        friend class detail::DynamicArrayDataHolderInterface;

    private:
        ALLOCATOR& allocator;
        ObjectArray<ObjectType*, MAX_NUM> pointers;
    };
}

#endif //OBJECT_ARRAY_DYNAMICARRAYDATAHOLDER_H
