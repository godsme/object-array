//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_DEDUCEINTOPTIONAL_H
#define OBJECT_ARRAY_DEDUCEINTOPTIONAL_H

#include <cub/base/IntOptional.h>

namespace detail {
    template<std::size_t MAX_SIZE>
    auto DeduceBitsType() -> auto {
        static_assert(MAX_SIZE <= (std::numeric_limits<std::size_t>::max() >> 1));
        if constexpr(MAX_SIZE <= (std::numeric_limits<uint8_t>::max() >> 1)) {
            return _7bits{};
        } else if constexpr(MAX_SIZE <= (std::numeric_limits<uint16_t>::max() >> 1)) {
            return _15bits{};
        } else if constexpr(MAX_SIZE <= (std::numeric_limits<uint32_t>::max() >> 1)) {
            return _31bits{};
        } else {
            return _63bits{};
        }
    }

    template<std::size_t MAX_SIZE>
    using DeduceIntOptional_t = IntOptional<decltype(DeduceBitsType<MAX_SIZE>())>;
}

#endif //OBJECT_ARRAY_DEDUCEINTOPTIONAL_H
