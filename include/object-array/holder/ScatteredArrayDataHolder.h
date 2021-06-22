//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H

#include <cub/base/DeduceSizeType.h>
#include <object-array/holder/ArrayDataHolder.h>

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ScatteredArrayDataHolderConcept {
        auto This() const -> DATA_HOLDER const * {
            return reinterpret_cast<DATA_HOLDER const*>(this);
        }
        using ElemType = typename DATA_HOLDER::ElemType;
        using ObjectType = typename DATA_HOLDER::ObjectType;

    public:
        auto GetRange() const -> auto { return This()->GetRange(); }
        auto Elems() const -> ElemType const* { return This()->Elems(); }
        static auto ElemToObject(ElemType const& elem) -> ObjectType const& {
            return DATA_HOLDER::ElemToObject(elem);
        }
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using SizeType = typename Parent::SizeType;
        using BitMap = typename Parent::BitMap;
        using ElemType = typename Parent::ElemType;
        using Concept = detail::ScatteredArrayDataHolderConcept<ScatteredArrayDataHolder>;

        auto GetScope() const -> decltype(auto) {
            return (occupied);
        }

        auto GetScope() -> decltype(auto) {
            return (occupied);
        }

        auto GetRange() const -> SizeType {
            return Parent::MAX_SIZE;
        }

    private:
        BitMap occupied;
    };
}

#endif //OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
