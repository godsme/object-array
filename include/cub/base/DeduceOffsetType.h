//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_DEDUCEOFFSETTYPE_H
#define OBJECT_ARRAY_DEDUCEOFFSETTYPE_H

#include <limits>
#include <cstdint>

namespace detail {
    template<std::size_t MAX_NUM>
    auto DeduceOffsetType() -> auto {
        static_assert(MAX_NUM <= std::numeric_limits<int32_t>::max());
        if constexpr(MAX_NUM <= std::numeric_limits<int8_t>::max()) {
            return int8_t{};
        } else if constexpr (MAX_NUM <= std::numeric_limits<int16_t>::max()) {
            return int16_t{};
        } else {
            return int32_t{};
        }
    }
}

template<std::size_t MAX_NUM>
using DeduceOffsetType_t = decltype(detail::DeduceOffsetType<MAX_NUM>());

#endif //OBJECT_ARRAY_DEDUCEOFFSETTYPE_H
