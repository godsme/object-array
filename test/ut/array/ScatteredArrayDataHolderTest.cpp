//
// Created by Darwin Yuan on 2021/6/21.
//

#include <l0-infra/array/holder/ScatteredArrayDataHolder.h>
#include <catch.hpp>

//
//namespace {
//    struct Foo {
//        explicit Foo(int a) : a{a} {}
//
//        int a;
//    };
//}
//
//SCENARIO("Object ScatteredArrayDataHolder") {
//    struct FooArray : holder::ScatteredArrayHolder<Foo, 5, FooArray> {
//        using Parent = holder::ScatteredArrayHolder<Foo, 5, FooArray>;
//        using Parent::Parent;
//    };
//
//    static_assert(std::is_same_v<Foo, FooArray::ObjectType>);
//    static_assert(std::is_same_v<Placement<Foo>, FooArray::ElemType>);
//    static_assert(5 == FooArray::MAX_SIZE);
//
//    static_assert(!std::is_trivially_default_constructible_v<FooArray>);
//    static_assert(std::is_trivially_destructible_v<FooArray>);
//
//    FooArray array;
//    REQUIRE(array.GetOccupied() == FooArray::BitMap{0});
//
//    array.Append(Foo{10});
//
//    REQUIRE(array.GetOccupied() == FooArray::BitMap{1});
//}