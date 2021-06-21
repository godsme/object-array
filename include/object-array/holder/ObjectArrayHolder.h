//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYHOLDER_H

#include <object-array/holder/ObjectArrayDataHolder.h>
#include <object-array/mixin/ContinuousArrayLike.h>
#include <object-array/mixin/RangedArray.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ObjectArrayHolder
            : ObjectArrayDataHolder<OBJ, MAX_NUM>
            , mixin::RangedArray<mixin::ContinuousArrayLike<ObjectArrayDataHolder<OBJ, MAX_NUM>>> {
    };
}

#endif //OBJECT_ARRAY_OBJECTARRAYHOLDER_H
