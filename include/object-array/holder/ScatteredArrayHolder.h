//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_SCATTEREDARRAYHOLDER_H
#define OBJECT_ARRAY_SCATTEREDARRAYHOLDER_H

#include <object-array/holder/ScatteredArrayDataHolder.h>
#include <object-array/mixin/RangedArray.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayHolder
            : ScatteredArrayDataHolder<OBJ, MAX_NUM>, mixin::RangedArray<ScatteredArrayDataHolder<OBJ, MAX_NUM>, false> {
        using DataHolder = ScatteredArrayDataHolder<OBJ, MAX_NUM>;
        using DataHolder::Elems;
    };
}

#endif //OBJECT_ARRAY_SCATTEREDARRAYHOLDER_H
