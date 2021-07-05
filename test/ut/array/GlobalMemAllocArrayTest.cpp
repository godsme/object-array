//
// Created by Darwin Yuan on 2021/7/6.
//

#include <l0-infra/array/MemAllocArray.h>
#include <catch.hpp>

SCENARIO("GlobalMemAllocArray Append") {
    GlobalMemAllocArray<int, 2> array{};
    REQUIRE(nullptr != array.Append(10));
    REQUIRE(nullptr != array.Append(20));
    REQUIRE(array.GetNum() == 2);
    REQUIRE(nullptr == array.Append(30));
}