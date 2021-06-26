//
// Created by Darwin Yuan on 2021/6/21.
//

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <catch.hpp>

SCENARIO("Int ObjectArrayDataHolder") {
    struct IntArray : holder::ObjectArrayDataHolder<int, 5, IntArray> {
        using Parent = holder::ObjectArrayDataHolder<int, 5, IntArray>;
        using Parent::Parent;
    };

    static_assert(std::is_same_v<int, IntArray::ObjectType>);
    static_assert(std::is_same_v<int, IntArray::ElemType>);
    static_assert(5 == IntArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<IntArray>);
    static_assert(std::is_trivially_destructible_v<IntArray>);
}

namespace {
    struct Foo {
        explicit Foo(int a) : a{a} {}

        int a;
    };
}

SCENARIO("Object ObjectArrayDataHolder") {
    struct FooArray : holder::ObjectArrayDataHolder<Foo, 5, FooArray> {
        using Parent = holder::ObjectArrayDataHolder<Foo, 5, FooArray>;
        using Parent::Parent;
    };

    static_assert(std::is_same_v<Foo, FooArray::ObjectType>);
    static_assert(std::is_same_v<Placement<Foo>, FooArray::ElemType>);
    static_assert(5 == FooArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<FooArray>);
    static_assert(std::is_trivially_destructible_v<FooArray>);
}
