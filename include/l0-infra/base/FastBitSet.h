//
// Created by Darwin Yuan on 2022/9/9.
//

#ifndef OBJECT_ARRAY_EB1FFFF3004E413ABA27CA51499201DC
#define OBJECT_ARRAY_EB1FFFF3004E413ABA27CA51499201DC

#include <cstddef>
#include <cstdint>
#include <limits>

template<std::size_t N>
struct FastBitSet {
    constexpr static std::size_t NUM_OF_INTS = (N + 63) / 64;
    constexpr static auto GetBytes(std::size_t n) -> std::size_t {
        return n >> 6;
    }
    constexpr static auto GetBits(std::size_t n) -> std::size_t {
        return n & 63;
    }
    constexpr static auto GetMask(std::size_t n) -> uint64_t {
        return (1ULL << n) - 1;
    }

    constexpr static uint64_t MASK_OF_LAST_INT = GetMask(GetBits(N));

    constexpr FastBitSet() = default;
    constexpr FastBitSet(FastBitSet const&) = default;
    constexpr FastBitSet(FastBitSet&&) = default;

    auto operator=(FastBitSet const&) -> FastBitSet& = default;
    auto operator=(FastBitSet&&) -> FastBitSet& = default;

    constexpr auto operator==(FastBitSet const& rhs) const -> bool {
        for(std::size_t i=0; i<NUM_OF_INTS; i++) {
            if(ints[i] != rhs.ints[i]) return false;
        }
        return true;
    }

    constexpr auto operator!=(FastBitSet const& rhs) const -> bool {
        return !operator==(rhs);
    }

    constexpr auto test(std::size_t pos) const -> bool {
        return (pos < N) && (ints[GetBytes(pos)] & (1ULL << GetBits(pos)));
    }

    constexpr auto operator[](std::size_t pos) const -> bool {
        return test(pos);
    }

    constexpr auto all() const -> bool {
        for(auto i=0; i<NUM_OF_INTS-1; i++) {
            if(ints[i] != std::numeric_limits<uint64_t>::max()) {
                return false;
            }
        }
        return MASK_OF_LAST_INT == ints[NUM_OF_INTS-1];
    }

    constexpr auto any() const -> bool {
        for(auto i=0; i<NUM_OF_INTS; i++) {
            if(ints[i] != 0) return true;
        }
        return false;
    }

    constexpr auto none() const -> bool {
        return !any();
    }

    constexpr auto count() const -> std::size_t {
        std::size_t c = 0;
        for(auto i=0; i<NUM_OF_INTS; i++) {
            c += __builtin_popcountll(ints[i]);
        }
        return c;
    }

    constexpr auto size() const -> std::size_t {
        return N;
    }

    auto set(std::size_t pos) -> FastBitSet& {
        if (pos < N) {
            ints[GetBytes(pos)] |= (1ULL << GetBits(pos));
        }
        return *this;
    }

    auto set() -> FastBitSet& {
        for(auto i=0; i<NUM_OF_INTS-1; i++) {
            ints[i] = std::numeric_limits<uint64_t>::max();
        }
        ints[NUM_OF_INTS-1] = MASK_OF_LAST_INT;
        return *this;
    }

    auto reset(std::size_t pos) noexcept -> FastBitSet& {
        if (pos < N) {
            ints[GetBytes(pos)] &= ~(1ULL << GetBits(pos));
        }
        return *this;
    }

    auto set(std::size_t pos, bool value) -> FastBitSet& {
        value ? set(pos) : reset(pos);
        return *this;
    }

    auto reset() -> FastBitSet& {
        for(auto i=0; i<NUM_OF_INTS; i++) {
            ints[i] = 0;
        }
        return *this;
    }

    auto flip() -> FastBitSet& {
        for(auto i=0; i<NUM_OF_INTS-1; i++) {
            ints[i] = ~ints[i];
        }
        ints[NUM_OF_INTS-1] = (~ints[NUM_OF_INTS-1] & MASK_OF_LAST_INT);
        return *this;
    }
private:
    uint64_t ints[NUM_OF_INTS]{};
};

#endif //OBJECT_ARRAY_EB1FFFF3004E413ABA27CA51499201DC
