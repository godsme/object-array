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
        using SizeType = typename DATA_HOLDER::SizeType;

    public:
        using BitMap = typename DATA_HOLDER::BitMap;
        auto GetRange() const -> SizeType { return This()->GetRange(); }
        auto Elems() const -> ElemType const* { return This()->Elems(); }
        static auto ElemToObject(ElemType const& elem) -> ObjectType const& {
            return DATA_HOLDER::ElemToObject(elem);
        }
        auto GetScope() const -> BitMap { return This()->GetScope(); }
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using SizeType = typename Parent::SizeType;
        using BitMap = typename Parent::BitMap;
        using ElemType = typename Parent::ElemType;
        using Interface = detail::ScatteredArrayDataHolderConcept<ScatteredArrayDataHolder>;

    public:
        ScatteredArrayDataHolder() {}
        ScatteredArrayDataHolder(std::initializer_list<OBJ> list) {
            auto n = std::min(list.size(), MAX_NUM);
            auto i = 0;
            for(auto&& elem : list) {
                occupied.set(i);
                Parent::elems[i++] = elem;
            }
        }

        auto GetScope() const -> BitMap {
            return occupied;
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
