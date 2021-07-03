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

    WHEN("Erase") {
        array.Erase(2);

        REQUIRE(array.GetNum() == 4);

        REQUIRE(array[0] == 7);
        REQUIRE(array[1] == 8);
        REQUIRE(array[2] == 10);
        REQUIRE(array[3] == 12);
    }

    WHEN("Clear") {
        array.Clear();
        REQUIRE(array.GetNum() == 0);
    }

    WHEN("Clear range") {
        array.Clear(1, 3);
        REQUIRE(array.GetNum() == 3);

        REQUIRE(array[0] == 7);
        REQUIRE(array[1] == 10);
        REQUIRE(array[2] == 12);
    }

    WHEN("Clear from") {
        array.ClearFrom(2);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0] == 7);
        REQUIRE(array[1] == 8);
    }

    WHEN("Clear Until") {
        array.ClearUntil(3);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0] == 10);
        REQUIRE(array[1] == 12);
    }
}

namespace {
    int object_count = 0;

    struct Foo {
        int a;
        explicit Foo(int a) : a{a} {}
        Foo(Foo const&) = default;
        auto operator=(Foo const&) -> Foo& = default;
        ~Foo() { a = 10; }
    };

    static_assert(!std::is_trivially_destructible_v<OrderedArray<Foo, 10>>);

    auto FooLess = [](auto&& l, auto&& r) {
        return l.a < r.a;
    };
}

SCENARIO("Foo OrderedArray") {
    OrderedArray<Foo, 10, decltype(FooLess)> array;

    array.Append(10);
    array.Append(8);
    array.Append(12);
    array.Append(7);
    array.Append(9);

    REQUIRE(array.GetNum() == 5);

    REQUIRE(array[0].a == 7);
    REQUIRE(array[1].a == 8);
    REQUIRE(array[2].a == 9);
    REQUIRE(array[3].a == 10);
    REQUIRE(array[4].a == 12);

    WHEN("Erase") {
        array.Erase(2);

        REQUIRE(array.GetNum() == 4);

        REQUIRE(array[0].a == 7);
        REQUIRE(array[1].a == 8);
        REQUIRE(array[2].a == 10);
        REQUIRE(array[3].a == 12);
    }

    WHEN("Clear") {
        array.Clear();
        REQUIRE(array.GetNum() == 0);
    }

    WHEN("Clear range") {
        array.Clear(1, 3);
        REQUIRE(array.GetNum() == 3);

        REQUIRE(array[0].a == 7);
        REQUIRE(array[1].a == 10);
        REQUIRE(array[2].a == 12);
    }

    WHEN("Clear from") {
        array.ClearFrom(2);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0].a == 7);
        REQUIRE(array[1].a == 8);
    }

    WHEN("Clear Until") {
        array.ClearUntil(3);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0].a == 10);
        REQUIRE(array[1].a == 12);
    }
}

SCENARIO("Foo Object OrderedArray") {
    OrderedArray<Foo, 10, decltype(FooLess)> array;

    array.Append(Foo{10});
    array.Append(Foo{8});
    array.Append(Foo{12});
    array.Append(Foo{7});
    array.Append(Foo{9});

    REQUIRE(array.GetNum() == 5);

    REQUIRE(array[0].a == 7);
    REQUIRE(array[1].a == 8);
    REQUIRE(array[2].a == 9);
    REQUIRE(array[3].a == 10);
    REQUIRE(array[4].a == 12);

    WHEN("Erase") {
        array.Erase(2);

        REQUIRE(array.GetNum() == 4);

        REQUIRE(array[0].a == 7);
        REQUIRE(array[1].a == 8);
        REQUIRE(array[2].a == 10);
        REQUIRE(array[3].a == 12);
    }

    WHEN("Clear") {
        array.Clear();
        REQUIRE(array.GetNum() == 0);
    }

    WHEN("Clear range") {
        array.Clear(1, 3);
        REQUIRE(array.GetNum() == 3);

        REQUIRE(array[0].a == 7);
        REQUIRE(array[1].a == 10);
        REQUIRE(array[2].a == 12);
    }

    WHEN("Clear from") {
        array.ClearFrom(2);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0].a == 7);
        REQUIRE(array[1].a == 8);
    }

    WHEN("Clear Until") {
        array.ClearUntil(3);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0].a == 10);
        REQUIRE(array[1].a == 12);
    }
}
