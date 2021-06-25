//
// Created by Darwin Yuan on 2021/6/21.
//

#include <l0-infra/array/holder/ScatteredArrayDataHolder.h>
#include <catch.hpp>

SCENARIO("Int ScatteredArrayDataHolder") {
    using IntArray = holder::ScatteredArrayHolder<int, 5>;
    static_assert(std::is_same_v<int, IntArray::ObjectType>);
    static_assert(std::is_same_v<int, IntArray::ElemType>);
    static_assert(5 == IntArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<IntArray>);
    static_assert(std::is_trivially_destructible_v<IntArray>);

    IntArray array;
    REQUIRE(array.GetOccupied() == 0);
    REQUIRE(array.GetOccupied() == IntArray::BitMap{0});
    array.Append(1);
    REQUIRE(array.GetOccupied() == IntArray::BitMap{1});
}

namespace {
    struct Foo {
        explicit Foo(int a) : a{a} {}

        int a;
    };
}

SCENARIO("Object ScatteredArrayDataHolder") {
    using FooArray = holder::ScatteredArrayHolder<Foo, 5>;
    static_assert(std::is_same_v<Foo, FooArray::ObjectType>);
    static_assert(std::is_same_v<Placement<Foo>, FooArray::ElemType>);
    static_assert(5 == FooArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<FooArray>);
    static_assert(std::is_trivially_destructible_v<FooArray>);

    FooArray array;
    REQUIRE(array.GetOccupied() == FooArray::BitMap{0});

    array.Append(Foo{10});

    REQUIRE(array.GetOccupied() == FooArray::BitMap{1});
}