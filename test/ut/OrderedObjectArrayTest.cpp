//
// Created by Darwin Yuan on 2021/7/9.
//

#include <l0-infra/array/OrderedObjectArray.h>
#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

namespace {
    using OrderedIntArray = OrderedObjectArray<int, 10>;
    static_assert(std::is_trivially_destructible_v<OrderedIntArray>);
}

SCENARIO("Const OrderedObjectArray init with init-list") {
    OrderedIntArray array{10,3,7,4};

    REQUIRE(array.GetNum() == 4);
    REQUIRE(array[0] == 3);
    REQUIRE(array[1] == 4);
    REQUIRE(array[2] == 7);
    REQUIRE(array[3] == 10);

    WHEN("Append") {
        array.Append(6);

        REQUIRE(array.GetNum() == 5);
        REQUIRE(array[0] == 3);
        REQUIRE(array[1] == 4);
        REQUIRE(array[2] == 6);
        REQUIRE(array[3] == 7);
        REQUIRE(array[4] == 10);
    }
}

namespace {
    using Indices = OrderedObjectArray<int, 10, std::function<auto (int, int) -> bool>>;
    static_assert(!std::is_trivially_destructible_v<Indices>);
}

SCENARIO("Indices init with less function") {
    ObjectArray<int, 10> array{3,6,5,2};
    Indices indices{[&](int l, int r) {
        return array[l] < array[r];
    }};

    indices.Append(0);
    indices.Append(1);
    indices.Append(2);
    indices.Append(3);

    REQUIRE(indices.GetNum() == 4);
    REQUIRE(indices[0] == 3);
    REQUIRE(indices[1] == 0);
    REQUIRE(indices[2] == 2);
    REQUIRE(indices[3] == 1);
}

SCENARIO("OrderedObjectArray") {
    OrderedObjectArray<int, 10> array;

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

    WHEN("Replace 0") {
        array.Replace(0, 1);

        REQUIRE(array[0] == 1);
        REQUIRE(array[1] == 8);
        REQUIRE(array[2] == 9);
        REQUIRE(array[3] == 10);
        REQUIRE(array[4] == 12);
    }

    WHEN("Replace 0") {
        array.Replace(4, 14);

        REQUIRE(array[0] == 7);
        REQUIRE(array[1] == 8);
        REQUIRE(array[2] == 9);
        REQUIRE(array[3] == 10);
        REQUIRE(array[4] == 14);
    }

    WHEN("Replace") {
        array.Replace(2, 11);

        REQUIRE(array[0] == 7);
        REQUIRE(array[1] == 8);
        REQUIRE(array[2] == 10);
        REQUIRE(array[3] == 11);
        REQUIRE(array[4] == 12);
    }

    WHEN("Replace 1") {
        array.Replace(2, 13);

        REQUIRE(array[0] == 7);
        REQUIRE(array[1] == 8);
        REQUIRE(array[2] == 10);
        REQUIRE(array[3] == 12);
        REQUIRE(array[4] == 13);
    }

    WHEN("Replace 2") {
        array.Replace(2, 6);

        REQUIRE(array[0] == 6);
        REQUIRE(array[1] == 7);
        REQUIRE(array[2] == 8);
        REQUIRE(array[3] == 10);
        REQUIRE(array[4] == 12);
    }

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

    static_assert(!std::is_trivially_destructible_v<OrderedObjectArray<Foo, 10>>);

    auto fooLess = [](Foo const& l, Foo const& r) {
        return l.a < r.a;
    };
}

SCENARIO("Foo OrderedObjectArray") {
    OrderedObjectArray<Foo, 10, decltype(fooLess)> array{fooLess};

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
