//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_INTBITSET_H
#define OBJECT_ARRAY_INTBITSET_H

#include <l0-infra/base/detail/DeduceBitSetIntType.h>
#include <limits>

template<std::size_t N>
struct IntBitSet {
private:
    constexpr static auto MAX_BITS = sizeof(std::size_t) * 8;
    static_assert(N > 0);
    static_assert(N <= MAX_BITS);
    using IntType = detail::DeduceBitSetIntType_t<N>;

    constexpr static auto GetMask(IntType n) -> auto {
        return n == MAX_BITS ? std::numeric_limits<std::size_t>::max() : ((1ULL << n) - 1);
    }

    constexpr static IntType MASK = GetMask(N);

public:
    constexpr static auto EnabledN(IntType n) -> IntBitSet {
        return IntBitSet(GetMask(n));
    }

public:
    constexpr IntBitSet() = default;
    constexpr IntBitSet(IntType integral) : integral(MASK & integral) {}

    constexpr IntBitSet(IntBitSet const&) = default;
    constexpr IntBitSet(IntBitSet&&) = default;

    auto operator=(IntBitSet const&) -> IntBitSet& = default;
    auto operator=(IntBitSet&&) -> IntBitSet& = default;

    constexpr auto operator==(IntBitSet const& rhs) const -> bool {
        return integral == rhs.integral;
    }

    constexpr auto operator!=(IntBitSet const& rhs) const -> bool {
        return integral != rhs.integral;
    }

    constexpr auto test(std::size_t pos) const -> bool {
        return (integral & (1ULL << pos)) > 0;
    }

    constexpr auto operator[](std::size_t pos) const -> bool {
        return test(pos);
    }

    constexpr auto all() const -> bool {
        return (integral & MASK) == MASK;
    }

    constexpr auto any() const -> bool {
        return integral > 0;
    }

    constexpr auto none() const -> bool {
        return integral == 0;
    }

    constexpr auto count() const -> std::size_t {
        std::size_t c = 0;
        for(auto n = integral; n > 0; n &= (n - 1)) c++;
        return c;
    }

    constexpr auto size() const -> std::size_t {
        return N;
    }

    auto set(std::size_t pos) -> IntBitSet& {
        integral |= (((IntType)1 << pos) & MASK);
        return *this;
    }

    auto set() -> IntBitSet& {
        integral = MASK;
        return *this;
    }

    auto set(std::size_t pos, bool value) -> IntBitSet& {
        value ? set(pos) : reset(pos);
        return *this;
    }

    auto reset(std::size_t pos) noexcept -> IntBitSet& {
        integral &= (~((IntType)1 << pos) & MASK);
        return *this;
    }

    auto reset() -> IntBitSet& {
        integral = 0;
        return *this;
    }

    auto flip() -> IntBitSet& {
        integral = (~integral & MASK);
        return *this;
    }

    auto operator&=(IntBitSet const& rhs) -> IntBitSet& {
        integral &= rhs.integral;
        return *this;
    }

    auto operator|=(IntBitSet const& rhs) -> IntBitSet& {
        integral |= rhs.integral;
        return *this;
    }

    auto operator^=(IntBitSet const& rhs) -> IntBitSet& {
        integral ^= rhs.integral;
        return *this;
    }

    constexpr auto operator<<(std::size_t pos) const -> IntBitSet {
        return IntBitSet(integral << pos);
    }

    auto operator<<=(std::size_t pos) -> IntBitSet& {
        integral <<= pos;
        integral &= MASK;
        return *this;
    }

    constexpr auto operator>>(std::size_t pos) const -> IntBitSet {
        return IntBitSet(integral >> pos);
    }

    auto operator>>=(std::size_t pos) -> IntBitSet& {
        integral >>= pos;
        return *this;
    }

    constexpr auto operator~() const -> IntBitSet {
        return IntBitSet(~integral);
    }

    constexpr auto to_ulong() const -> unsigned long {
        return integral;
    }

    friend constexpr auto operator&(IntBitSet const& lhs, IntBitSet const rhs) -> IntBitSet {
        return IntBitSet(lhs.integral & rhs.integral);
    }

    friend constexpr auto operator|(IntBitSet const& lhs, IntBitSet const rhs) -> IntBitSet {
        return IntBitSet(lhs.integral | rhs.integral);
    }

    friend constexpr auto operator^(IntBitSet const& lhs, IntBitSet const rhs) -> IntBitSet {
        return IntBitSet(lhs.integral ^ rhs.integral);
    }

private:
    IntType integral{};
};

#endif //OBJECT_ARRAY_INTBITSET_H
