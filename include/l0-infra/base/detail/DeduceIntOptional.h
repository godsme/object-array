//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_DEDUCEINTOPTIONAL_H
#define OBJECT_ARRAY_DEDUCEINTOPTIONAL_H

#include <l0-infra/base/IntOpt.h>

namespace detail {
    template<std::size_t MAX_SIZE>
    auto DeduceIntOptSizeType() -> auto {
        static_assert(MAX_SIZE < (std::numeric_limits<std::size_t>::max()));
        if constexpr(MAX_SIZE < (std::numeric_limits<uint8_t>::max())) {
            return uint8_t{};
        } else if constexpr(MAX_SIZE < std::numeric_limits<uint16_t>::max()) {
            return uint16_t{};
        } else if constexpr(MAX_SIZE < std::numeric_limits<uint32_t>::max()) {
            return uint32_t{};
        } else {
            return uint64_t{};
        }
    }

    template<std::size_t MAX_SIZE>
    using DeduceIntOptSizeType_t = decltype(DeduceIntOptSizeType<MAX_SIZE>());

    template<std::size_t MAX_SIZE>
    using DeduceIntOpt_t = IntOpt<DeduceIntOptSizeType_t<MAX_SIZE>>;
}

#endif //OBJECT_ARRAY_DEDUCEINTOPTIONAL_H
