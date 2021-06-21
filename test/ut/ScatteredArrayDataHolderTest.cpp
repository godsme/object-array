//
// Created by Darwin Yuan on 2021/6/21.
//

#include <object-array/holder/ScatteredArrayDataHolder.h>
#include <catch.hpp>

SCENARIO("ScatteredArrayDataHolder") {
    using IntArray = holder::ScatteredArrayDataHolder<int, 5>;
    static_assert(std::is_same_v<int, IntArray::ObjectType>);
    static_assert(std::is_same_v<int, IntArray::ElemType>);
    static_assert(5 == IntArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<IntArray>);
    static_assert(std::is_trivially_destructible_v<IntArray>);

    IntArray array;
    REQUIRE(array.occupied == 0);
    REQUIRE(array.GetRange() == 5);
    REQUIRE(array.GetScope() == IntArray::BitMap{0});

    array.elems[0] = 1;
    array.occupied.set(0);

    REQUIRE(array.GetRange() == 5);
    REQUIRE(array.GetScope() == IntArray::BitMap{1});

    array.GetScope().set(1);
    REQUIRE(array.GetScope() == IntArray::BitMap{3});

    REQUIRE(IntArray::ElemToObject(array.elems[0]) == 1);
}