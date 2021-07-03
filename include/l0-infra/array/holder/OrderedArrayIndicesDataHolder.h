//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_ORDEREDARRAYINDICESDATAHOLDER_H
#define OBJECT_ARRAY_ORDEREDARRAYINDICESDATAHOLDER_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>

namespace holder {
    template<std::size_t MAX_SIZE, typename Parent = detail::ObjectArrayHolder<DeduceSizeType_t<MAX_SIZE>, MAX_SIZE, true>>
    class OrderedArrayIndicesDataHolder : public Parent {
    public:
        using Parent::Parent;
    };
}

#endif //OBJECT_ARRAY_ORDEREDARRAYINDICESDATAHOLDER_H
