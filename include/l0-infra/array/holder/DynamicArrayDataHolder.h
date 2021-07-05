//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICARRAYDATAHOLDER_H
#define OBJECT_ARRAY_DYNAMICARRAYDATAHOLDER_H

#include <l0-infra/array/detail/ArrayIndices.h>

namespace holder::detail {
    template<typename HOLDER>
    class DynamicArrayDataHolderInterface {
        dEcL_tHiS(DATA_HOLDER);
    public:
        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        auto GetObj(SizeType n) -> ObjectType& { return *(This()->pointers[n]); }
        auto GetObj(SizeType n) const -> ObjectType const& { return *(This()->pointers[n]); }
        auto Num() const -> SizeType { return This()->pointers.GetNum(); }
    };
}

namespace holder {
    template<typename ALLOCATOR, std::size_t MAX_NUM>
    struct DynamicArrayDataHolder {
        using ObjectType = typename ALLOCATOR::ObjectType;
        using PointerArray = ObjectArray<ObjectType*, MAX_NUM>;
        using SizeType = typename PointerArray::SizeType;
        constexpr static SizeType MAX_SIZE = MAX_NUM;

        using Interface = DynamicArrayDataHolderInterface<DynamicArrayDataHolder>;

    private:
        auto ClearContent() {
            for(auto* pointer : pointers) {
                ALLOCATOR.Remove(pointer);
            }
        }

        auto DoClear() {
            ClearContent();
            pointers.Clear();
        }

        auto CopyFrom(DynamicArrayDataHolder const& rhs) {
            if(!allocator.HasEnoughSlots(rhs.pointers.GetNum())) { return; }
            for(auto* pointer : rhs.pointers) {
                auto* p = allocator.Append(*pointer);
                if(p == nullptr) {
                    DoClear();
                    return;
                }
                pointers.Append(allocator.Append(*pointer));
            }
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
            if(allocator != rhs.allocator) return;
            DoClear();
            CopyFrom(rhs);
            return *this;
        }

        auto operator=(DynamicArrayDataHolder&& rhs) -> DynamicArrayDataHolder& {
            if(allocator != rhs.allocator) return;
            DoClear();
            pointers = std::move(rhs.pointers);
            return *this;
        }

        ~DynamicArrayDataHolder() {
            ClearContent();
        }

    private:
        template<typename>
        friend detail::DynamicArrayDataHolderInterface;

    private:
        ALLOCATOR& allocator;
        ObjectArray<ObjectType*, MAX_NUM> pointers;
    };
}

#endif //OBJECT_ARRAY_DYNAMICARRAYDATAHOLDER_H
