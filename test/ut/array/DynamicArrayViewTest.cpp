//
// Created by Darwin Yuan on 2021/7/6.
//

#include <l0-infra/array/ScatteredArray.h>
#include <l0-infra/array/DynamicArrayView.h>
#include <catch.hpp>

namespace {
    struct Foo {
        int* array[2];
        uint16_t num;
    };
}
SCENARIO("DynamicArrayView Append") {
    ScatteredArray<int, 10> allocator;
    {
        Foo foo;
        DynamicArrayView array{allocator, foo.array, foo.num = 0};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(allocator.GetNum() == 1);
        REQUIRE(nullptr != array.Append(20));
        REQUIRE(allocator.GetNum() == 2);
        REQUIRE(nullptr == array.Append(30));
    }
    REQUIRE(allocator.GetNum() == 2);
}