//
// Created by Darwin Yuan on 2021/6/25.
//

#include <l0-infra/base/IntBitSet.h>
#include <l0-infra/base/BitSet.h>
#include <catch.hpp>

SCENARIO("IntBitSet Size") {
    static_assert(sizeof(IntBitSet<8>) == 1);
    static_assert(sizeof(IntBitSet<9>) == 2);
    static_assert(sizeof(IntBitSet<16>) == 2);
    static_assert(sizeof(IntBitSet<17>) == 4);
    static_assert(sizeof(IntBitSet<32>) == 4);
    static_assert(sizeof(IntBitSet<33>) == 8);
    static_assert(sizeof(IntBitSet<64>) == 8);
}

SCENARIO("IntBitSet Count") {
    REQUIRE(IntBitSet<8>{0xFF}.count() == 8);
    REQUIRE(IntBitSet<8>{0xFE}.count() == 7);
    REQUIRE(IntBitSet<8>{0x02}.count() == 1);
}

SCENARIO("IntBitSet Flip") {
    IntBitSet<8> bitSet{0xFF};

    REQUIRE(bitSet[0]);

    bitSet.flip();
    REQUIRE(bitSet == IntBitSet<8>{0});
    REQUIRE(bitSet.none());
    REQUIRE(!bitSet.any());

    REQUIRE(!bitSet[0]);

    bitSet.flip();
    REQUIRE(!bitSet.none());
    REQUIRE(bitSet.any());
    REQUIRE(bitSet.all());
    REQUIRE(bitSet[0]);

    bitSet = IntBitSet<8>{0xFE};
    REQUIRE(!bitSet.none());
    REQUIRE(bitSet.any());
    REQUIRE(!bitSet.all());
    REQUIRE(!bitSet[0]);
}

SCENARIO("IntBitSet set/reset") {
    IntBitSet<8> bitSet{};

    REQUIRE(!bitSet[1]);
    bitSet.set(1);
    REQUIRE(bitSet[1]);

    REQUIRE(bitSet == IntBitSet<8>{2});

    bitSet.set(9);
    REQUIRE(bitSet == IntBitSet<8>{2});
    REQUIRE(!bitSet[9]);

    bitSet.reset(1);
    REQUIRE(bitSet == IntBitSet<8>{0});

    IntBitSet<7> bs;

    bs.set(7);
    REQUIRE(bs == IntBitSet<7>{0});

    bs.set();
    REQUIRE(bs == IntBitSet<7>{0x7F});
    bs.reset();
    REQUIRE(bs == IntBitSet<7>{0});

    bs.set(1, true);
    REQUIRE(bs == IntBitSet<7>{2});
    bs.set(1, false);
    REQUIRE(bs == IntBitSet<7>{0});
}

SCENARIO("IntBitSet bi-op") {
    REQUIRE((IntBitSet<7>(0x2) | IntBitSet<7>(0x01)) == IntBitSet<7>(0x03));
    REQUIRE((IntBitSet<7>(0x2) & IntBitSet<7>(0x03)) == IntBitSet<7>(0x02));
    REQUIRE(~IntBitSet<7>(0x2) == IntBitSet<7>{0x7D});

    REQUIRE((IntBitSet<7>{} ^ IntBitSet<7>{}) == IntBitSet<7>{});

    REQUIRE((IntBitSet<7>(0x2) >> 1) == IntBitSet<7>(0x1));
    REQUIRE((IntBitSet<7>(0x2) << 1) == IntBitSet<7>(0x4));

    {
        IntBitSet<7> a(0x2);
        a <<= 1;
        REQUIRE(a == IntBitSet<7>(0x4));
    }

    {
        IntBitSet<7> a(0x2);
        a >>= 1;
        REQUIRE(a == IntBitSet<7>(0x1));
    }

};