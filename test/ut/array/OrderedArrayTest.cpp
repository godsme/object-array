//
// Created by Darwin Yuan on 2021/7/2.
//
#include <l0-infra/array/OrderedArray.h>
#include <catch.hpp>

SCENARIO("OrderedArray") {
    OrderedArray<int, 10> array;

    array.Append(10);
    array.Append(8);
    array.Append(12);
    array.Append(7);
    array.Append(9);

    REQUIRE(array.GetNum() == 5);

    REQUIRE(array[0] == 7);
    REQUIRE(array[1] == 8);
    REQUIRE(array[2] == 9);
    REQUIRE(array[3] == 10);
    REQUIRE(array[4] == 12);
}
