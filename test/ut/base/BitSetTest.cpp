//
// Created by Darwin Yuan on 2021/6/25.
//

#include <l0-infra/base/BitSet.h>
#include <catch.hpp>

static_assert(std::is_trivially_copyable_v<IntBitSet<10>>);
static_assert(std::is_trivially_destructible_v<IntBitSet<10>>);

SCENARIO("BitSet Size") {
    static_assert(sizeof(BitSet<8>) == 1);
    static_assert(sizeof(BitSet<9>) == 2);
    static_assert(sizeof(BitSet<16>) == 2);
    static_assert(sizeof(BitSet<17>) == 4);
    static_assert(sizeof(BitSet<32>) == 4);
    static_assert(sizeof(BitSet<33>) == 8);
    static_assert(sizeof(BitSet<64>) == 8);
    static_assert(sizeof(BitSet<65>) == sizeof(std::bitset<65>));
    static_assert(sizeof(BitSet<256>) == sizeof(std::bitset<256>));
}