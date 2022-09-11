//
// Created by Darwin Yuan on 2022/9/11.
//
#include <catch.hpp>
#include <l0-infra/base/FastBitSet.h>

SCENARIO("FastBitSet") {
    FastBitSet<100> bitSet;
    REQUIRE(bitSet.none());
    REQUIRE_FALSE(bitSet.all());
    REQUIRE(bitSet.flip().all());
    REQUIRE(bitSet.count() == 100);
    REQUIRE(bitSet.reset().none());
    REQUIRE(bitSet.count() == 0);
    bitSet.set(99);
    REQUIRE(bitSet.count() == 1);
    REQUIRE(bitSet[99]);
}