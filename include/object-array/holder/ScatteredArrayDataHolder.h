//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H

#include <cub/base/DeduceSizeType.h>
#include <object-array/holder/ArrayDataHolder.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        auto GetScope() const -> decltype(auto) {
            return (occupied);
        }

        auto GetScope() -> decltype(auto) {
            return (occupied);
        }

        auto GetRange() const -> SizeType {
            return MAX_NUM;
        }

        BitMap occupied;
    };
}

#endif //OBJECT_ARRAY_SCATTEREDARRAYDATAHOLDER_H
