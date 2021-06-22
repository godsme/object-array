//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H

#include <cub/base/DeduceSizeType.h>
#include <object-array/holder/ArrayDataHolder.h>

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ArrayDataHolderConcept {
        auto This() const -> DATA_HOLDER const * {
            return reinterpret_cast<DATA_HOLDER const*>(this);
        }
    public:
        using ElemType = typename DATA_HOLDER::ElemType;
        using ObjectType = typename DATA_HOLDER::ObjectType;

        auto Elems() const -> decltype(auto) {
            return (This()->Elems());
        }

        auto Num() const -> decltype(auto) {
            return (This()->Num());
        }

        static auto ElemToObject(ElemType const& elem) -> ObjectType const& {
            return DATA_HOLDER::ElemToObject(elem);
        }
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ObjectArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using SizeType = typename Parent::SizeType;
        using Concept = detail::ArrayDataHolderConcept<ObjectArrayDataHolder>;

        auto Num() const -> decltype(auto) { return (num); }
        auto Num() -> decltype(auto) { return (num); }

    private:
        SizeType num{};
    };
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
