//
// Created by Darwin Yuan on 2021/7/2.
//

#ifndef OBJECT_ARRAY_ORDEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_ORDEREDARRAYDATAHOLDER_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>

namespace holder::detail {
    template<typename DATA_HOLDER, typename COMPARE>
    struct OrderedArrayInterface : ContinuousArrayDataHolderInterface<DATA_HOLDER> {
        using typename ContinuousArrayDataHolderInterface<DATA_HOLDER>::ObjectType;
        using Compare = COMPARE;
    };

    template<typename OBJ, std::size_t MAX_SIZE, typename COMPARE>
    struct OrderedArrayDataHolder : ObjectArrayHolder<OBJ, MAX_SIZE, true> {
        using Parent = ObjectArrayHolder<OBJ, MAX_SIZE, true>;
        using Parent::Parent;
        using Interface = OrderedArrayInterface<OrderedArrayDataHolder, COMPARE>;
    };

    template <typename COMPARE>
    struct OrderedArrayHolder {
        template<typename OBJ, std::size_t MAX_SIZE>
        using Type = OrderedArrayDataHolder<OBJ, MAX_SIZE, COMPARE>;
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_SIZE, typename COMPARE>
    using OrderedArrayHolder = detail::Holder<OBJ, MAX_SIZE, detail::OrderedArrayHolder<COMPARE>::template Type>;
}

#endif //OBJECT_ARRAY_ORDEREDARRAYDATAHOLDER_H
