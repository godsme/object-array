//
// Created by Darwin Yuan on 2021/6/30.
//

#ifndef OBJECT_ARRAY_VIEWDATAHOLDER_H
#define OBJECT_ARRAY_VIEWDATAHOLDER_H

#include <type_traits>

namespace holder::detail {
    template<typename ARRAY>
    struct ViewDataHolder {
        constexpr static auto IS_CONST = std::is_const_v<ARRAY> || ARRAY::IS_CONST;
        using ArrayType = std::decay_t<ARRAY>;
        using ObjectType = std::conditional_t<IS_CONST, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using SizeType = typename ArrayType::SizeType;
        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;
    };
}

#endif //OBJECT_ARRAY_VIEWDATAHOLDER_H
