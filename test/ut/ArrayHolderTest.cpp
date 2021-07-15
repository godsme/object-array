//
// Created by Darwin Yuan on 2021/7/8.
//

#include <l0-infra/array/holder/detail/ArrayHolder.h>
#include <catch.hpp>

namespace {
    using OrderedIntArray = holder::detail::ArrayHolder<int, 0xFF, true>;
    static_assert(std::is_trivially_destructible_v<OrderedIntArray>);
    static_assert(!std::is_trivially_default_constructible_v<OrderedIntArray>);
    static_assert(std::is_same_v<OrderedIntArray::SizeType, uint16_t>);
    static_assert(std::is_same_v<OrderedIntArray::ObjectType, int>);
    static_assert(!OrderedIntArray::IS_CONST);
    static_assert(OrderedIntArray::IS_ORDERED);

    using IntArray = holder::detail::ArrayHolder<int, 0xFF-1, false>;
    static_assert(std::is_trivially_destructible_v<IntArray>);
    static_assert(!std::is_trivially_default_constructible_v<IntArray>);
    static_assert(std::is_same_v<IntArray::SizeType, uint8_t>);
    static_assert(!IntArray::IS_ORDERED);

    using ConstIntArray = holder::detail::ArrayHolder<int const, 0xFF-1, false>;
    static_assert(std::is_trivially_destructible_v<ConstIntArray>);
    static_assert(!std::is_trivially_default_constructible_v<ConstIntArray>);
    static_assert(std::is_same_v<ConstIntArray::SizeType, uint8_t>);
    static_assert(ConstIntArray::IS_CONST);
    static_assert(!IntArray::IS_ORDERED);

    template<typename T>
    struct Array : T {
        using T::T;
        Array() {}

        using T::elems;
    };
}

SCENARIO("Const Array could be initialized by init_list") {
    Array<ConstIntArray> array{1,2,3,4};
    REQUIRE(array.elems[0] == 1);
    REQUIRE(array.elems[1] == 2);
    REQUIRE(array.elems[2] == 3);
    REQUIRE(array.elems[3] == 4);
}

SCENARIO("Placement of trivial type should not be 0-initialized") {
    Placement<Placement<int>> value;
    ::memset(&value, 0xFF, sizeof(value));
    value.Emplace();

    REQUIRE((*value).GetObj() != 0);
}

SCENARIO("Default Array Initialization of trivial type should not be 0-initialized") {
    Placement<Array<ConstIntArray>> array;
    ::memset(&array, 0xFF, sizeof(array));
    array.Emplace();

    REQUIRE(array->elems[0] != 0);
}

namespace {
    struct Foo {
        ~Foo() {}
        int a{};
    };

    static_assert(!std::is_trivially_destructible_v<Foo>);
    static_assert(!std::is_trivially_destructible_v<Placement<Foo>>);

    using ConstOrderedFooArray = holder::detail::ArrayHolder<Foo const, 0xFF-1, true>;
    static_assert(!std::is_trivially_destructible_v<ConstOrderedFooArray>);
    static_assert(!std::is_trivially_default_constructible_v<ConstOrderedFooArray>);
    static_assert(std::is_same_v<ConstOrderedFooArray::SizeType, uint8_t>);
    static_assert(ConstOrderedFooArray::IS_CONST);
    static_assert(ConstOrderedFooArray::IS_ORDERED);
}

SCENARIO("Default Array Initialization of non-trivial type should not be 0-initialized") {
    Placement<Array<ConstOrderedFooArray>> array;
    ::memset(&array, std::numeric_limits<int>::max(), sizeof(array));
    array.Emplace();

    REQUIRE(array->elems[0]->a != 0);
}

