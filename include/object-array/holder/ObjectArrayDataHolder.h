//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H

#include <cub/base/DeduceSizeType.h>
#include <object-array/holder/ArrayDataHolder.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ObjectArrayDataHolder : ArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM>;
        using SizeType = typename Parent::SizeType;

        auto GetRange() const -> SizeType {
            return num;
        }

        SizeType num{};
    };
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
