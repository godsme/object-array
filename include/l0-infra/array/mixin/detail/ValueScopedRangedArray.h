//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_VALUESCOPEDRANGEDARRAY_H
#define OBJECT_ARRAY_VALUESCOPEDRANGEDARRAY_H

namespace mixin::detail {
    template<typename HOLDER, typename SCOPED_ARRAY_LIKE>
    struct ValueScopedRangedArray : private HOLDER, SCOPED_ARRAY_LIKE {
        using HOLDER::HOLDER;
        using SCOPED_ARRAY_LIKE::IndexBegin;
        using SCOPED_ARRAY_LIKE::IndexEnd;
        using SCOPED_ARRAY_LIKE::GetScope;
        using SCOPED_ARRAY_LIKE::GetObj;

        using typename HOLDER::SizeType;
        using typename HOLDER::ObjectType;
        using typename SCOPED_ARRAY_LIKE::BitMap;

        constexpr static auto MAX_SIZE = HOLDER::MAX_SIZE;

        ValueScopedRangedArray(ValueScopedRangedArray&&) = default;
        ValueScopedRangedArray(ValueScopedRangedArray const&) = default;
    };
}

#endif //OBJECT_ARRAY_VALUESCOPEDRANGEDARRAY_H
