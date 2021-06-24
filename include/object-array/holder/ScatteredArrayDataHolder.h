//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H

#include <object-array/holder/ArrayDataHolder.h>
#include <object-array/holder/detail/ArrayDataHolderInterface.h>


namespace holder::detail {
    template<typename DATA_HOLDER>
    class ScatteredArrayDataHolderInterface : public ArrayDataHolderInterface<DATA_HOLDER>{
        dEcL_tHiS(DATA_HOLDER);
    public:
        using SizeType = typename DATA_HOLDER::SizeType;
        using BitMap = typename DATA_HOLDER::BitMap;

        auto GetRange() const -> SizeType { return DATA_HOLDER::MAX_SIZE; }
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
        using Interface = detail::ScatteredArrayDataHolderInterface<ScatteredArrayDataHolder>;

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

    private:
        BitMap occupied;
    };
}

#endif //OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
