//
// Created by Darwin Yuan on 2021/6/21.
//

#include <object-array/holder/ScatteredArrayDataHolder.h>
#include <catch.hpp>

SCENARIO("Int ScatteredArrayDataHolder") {
    using IntArray = holder::ScatteredArrayDataHolder<int, 5>;
    static_assert(std::is_same_v<int, IntArray::ObjectType>);
    static_assert(std::is_same_v<int, IntArray::ElemType>);
    static_assert(5 == IntArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<IntArray>);
    static_assert(std::is_trivially_destructible_v<IntArray>);

    IntArray array;
    REQUIRE(array.GetScope() == 0);
    REQUIRE(array.GetRange() == 5);
    REQUIRE(array.GetScope() == IntArray::BitMap{0});

    array.Elems()[0] = 1;
    array.GetScope().set(0);

    REQUIRE(array.GetRange() == 5);
    REQUIRE(array.GetScope() == IntArray::BitMap{1});

    array.GetScope().set(1);
    REQUIRE(array.GetScope() == IntArray::BitMap{3});

    REQUIRE(IntArray::ElemToObject(array.Elems()[0]) == 1);
}

namespace {
    struct Foo {
        explicit Foo(int a) : a{a} {}

        int a;
    };
}

SCENARIO("Object ScatteredArrayDataHolder") {
    using FooArray = holder::ScatteredArrayDataHolder<Foo, 5>;
    static_assert(std::is_same_v<Foo, FooArray::ObjectType>);
    static_assert(std::is_same_v<Placement<Foo>, FooArray::ElemType>);
    static_assert(5 == FooArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<FooArray>);
    static_assert(std::is_trivially_destructible_v<FooArray>);

    FooArray array;
    REQUIRE(array.GetScope() == 0);
    REQUIRE(array.GetRange() == 5);
    REQUIRE(array.GetScope() == FooArray::BitMap{0});

    array.Elems()[0].Emplace(Foo{10});
    array.GetScope().set(0);

    REQUIRE(array.GetRange() == 5);
    REQUIRE(array.GetScope() == FooArray::BitMap{1});

    array.GetScope().set(1);
    REQUIRE(array.GetScope() == FooArray::BitMap{3});

    REQUIRE(FooArray::ElemToObject(array.Elems()[0]).a == Foo{10}.a);
}