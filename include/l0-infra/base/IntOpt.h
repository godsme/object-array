//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INTOPT_H
#define OBJECT_ARRAY_INTOPT_H

#include <optional>

template<typename T, T EMPTY = std::is_signed_v<T> ? std::numeric_limits<T>::min() : std::numeric_limits<T>::max()>
class IntOpt {
    static_assert
           (std::is_same_v<T, uint8_t> ||
            std::is_same_v<T, uint16_t> ||
            std::is_same_v<T, uint32_t> ||
            std::is_same_v<T, uint64_t> ||
            std::is_same_v<T, int8_t>   ||
            std::is_same_v<T, int16_t>  ||
            std::is_same_v<T, int32_t>  ||
            std::is_same_v<T, int64_t>);
    using IntType = T;

public:
    IntOpt() {}
    IntOpt(IntType value)  : value_(value) {}
    IntOpt(std::nullopt_t) : value_(EMPTY) {}
    IntOpt(IntOpt const& rhs) = default;

    auto reset() -> void { value_ = EMPTY; }

    auto operator=(IntOpt const& rhs) -> IntOpt& = default;
    auto operator=(std::nullopt_t const&) -> IntOpt& {
        reset();
        return *this;
    }

    auto has_value() const -> bool { return value_ != EMPTY; }
    explicit operator bool() const { return has_value(); }

    auto value() const -> IntType { return value_; }
    auto operator*() const -> IntType { return value_; }

    auto value_or(IntType v) const -> IntType {
        return has_value() ? value_ : v;
    }

    auto emplace(IntType value) -> void {
        value_ = value;
    }

    auto operator==(IntOpt const& rhs) const -> bool { return value_ == rhs.value_; }
    auto operator!=(IntOpt const& rhs) const -> bool { return !operator==(rhs); }

    friend auto operator==(IntOpt const& lhs, std::nullopt_t const&) -> bool { return lhs.value_ == EMPTY; }
    friend auto operator==(std::nullopt_t const& lhs, IntOpt const& rhs) -> bool { return rhs.value_ == EMPTY; }
    friend auto operator!=(IntOpt const& lhs, std::nullopt_t const& rhs) -> bool { return !(lhs==rhs); }
    friend auto operator!=(std::nullopt_t const& lhs, IntOpt const& rhs) -> bool { return !(lhs==rhs); }

private:
    IntType value_{EMPTY};
};

#endif //OBJECT_ARRAY_INTOPT_H
