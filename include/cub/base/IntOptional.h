//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INTOPTIONAL_H
#define OBJECT_ARRAY_INTOPTIONAL_H

#include <optional>

namespace detail {
    template<std::size_t MAX_SIZE>
    auto DeduceUintType() -> auto {
        static_assert(MAX_SIZE <= (std::numeric_limits<std::size_t>::max() >> 1));
        if constexpr(MAX_SIZE <= (std::numeric_limits<uint8_t>::max() >> 1)) {
            return uint8_t{};
        } else if constexpr(MAX_SIZE <= (std::numeric_limits<uint16_t>::max() >> 1)) {
            return uint16_t{};
        } else if constexpr(MAX_SIZE <= (std::numeric_limits<uint32_t>::max() >> 1)) {
            return uint32_t{};
        } else {
            return std::size_t{};
        }
    }
}

template<std::size_t MAX_SIZE>
class IntOptional {
    using IntType = decltype(detail::DeduceUintType<MAX_SIZE>());
    constexpr static auto MAX_BITS = (sizeof(IntType) << 3) - 1;
    constexpr static IntType EMPTY = 1 << MAX_BITS;
    constexpr static IntType VALUE_MASK = ~EMPTY;

public:
    IntOptional() {}
    IntOptional(IntType value)  : value_(VALUE_MASK & value) {}
    IntOptional(std::nullopt_t) : value_(EMPTY) {}
    IntOptional(IntOptional const& rhs) = default;

    auto reset() -> void { value_ = EMPTY; }

    auto operator=(IntOptional const& rhs) -> IntOptional& = default;
    auto operator=(std::nullopt_t const&) -> IntOptional& {
        reset();
        return *this;
    }

    auto has_value() const -> bool { return value_ != EMPTY; }
    operator bool() const { return has_value(); }

    auto value() const -> IntType { return value_; }
    auto operator*() const -> IntType { return value_; }

    auto value_or(IntType v) const -> IntType {
        return has_value() ? value_ : v;
    }

    auto emplace(IntType value) -> void {
        value_ = VALUE_MASK & value;
    }

    auto operator==(IntOptional const& rhs) const -> bool { return value_ == rhs.value_; }
    auto operator!=(IntOptional const& rhs) const -> bool { return !operator==(rhs); }

    friend auto operator==(IntOptional const& lhs, std::nullopt_t const&) -> bool { return lhs.value_ == EMPTY; }
    friend auto operator==(std::nullopt_t const& lhs, IntOptional const& rhs) -> bool { return rhs.value_ == EMPTY; }
    friend auto operator!=(IntOptional const& lhs, std::nullopt_t const& rhs) -> bool { return !(lhs==rhs); }
    friend auto operator!=(std::nullopt_t const& lhs, IntOptional const& rhs) -> bool { return !(lhs==rhs); }

private:
    IntType value_{EMPTY};
};

#endif //OBJECT_ARRAY_INTOPTIONAL_H
