//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_VALUERANGEDARRAY_H
#define OBJECT_ARRAY_VALUERANGEDARRAY_H

namespace mixin::detail {
    template<typename HOLDER, typename RANGED_ARRAY_LIKE>
    struct ValueRangedArray : private HOLDER, RANGED_ARRAY_LIKE {
        using HOLDER::HOLDER;
        using RANGED_ARRAY_LIKE::GetObj;
        using RANGED_ARRAY_LIKE::IndexBegin;
        using RANGED_ARRAY_LIKE::IndexEnd;

        using typename HOLDER::SizeType;
        using typename HOLDER::ObjectType;
        using typename HOLDER::ElemType;

        constexpr static auto MAX_SIZE = HOLDER::MAX_SIZE;
        ValueRangedArray(ValueRangedArray&&) = default;
    };
}

#endif //OBJECT_ARRAY_VALUERANGEDARRAY_H
