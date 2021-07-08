//
// Created by Darwin Yuan on 2021/7/2.
//
#include <l0-infra/array/OrderedObjectArray.h>
#include <catch.hpp>

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

    WHEN("Range for") {
        int a[10];
        int n = 0;
        for(auto&& elem : array) {
            a[n++] = elem;
        }

        REQUIRE(n == 5);

        REQUIRE(a[0] == 7);
        REQUIRE(a[1] == 8);
        REQUIRE(a[2] == 9);
        REQUIRE(a[3] == 10);
        REQUIRE(a[4] == 12);
    }

    WHEN("Range for with index") {
        int a[10];
        int n = 0;
        for(auto&& [elem, i] : array.WithIndex()) {
            REQUIRE(n == i);
            a[n++] = elem;
        }

        REQUIRE(n == 5);

        REQUIRE(a[0] == 7);
        REQUIRE(a[1] == 8);
        REQUIRE(a[2] == 9);
        REQUIRE(a[3] == 10);
        REQUIRE(a[4] == 12);
    }

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

SCENARIO("Ordered Slice Append") {
    OrderedObjectArray<int, 10> array = {4,3,1,2};
    auto&& slice = array.From(1);

    REQUIRE(slice.GetNum() == 3);

    WHEN("Append") {
        auto* p = slice.Append(5);
        REQUIRE(*p == 5);
        REQUIRE(slice.GetNum() == 4);
        REQUIRE(slice[3] == 5);
    }

    WHEN("Replace") {
        auto* p = slice.Replace(0, 10);
        REQUIRE(*p == 10);
        REQUIRE(slice.GetNum() == 3);
        REQUIRE(slice[0] == 3);
        REQUIRE(slice[1] == 4);
        REQUIRE(slice[2] == 10);
        REQUIRE(array[3] == 10);
    }
}

SCENARIO("OrderedObjectArray Scope Append") {
    OrderedObjectArray<int, 10> array = {4,3,1,2};
    auto&& scope = array.Scope(0x0a);

    REQUIRE(scope.GetNum() == 2);

    WHEN("Append") {
        auto* p = scope.Append(0);
        REQUIRE(*p == 0);
        REQUIRE(scope.GetNum() == 2);
        REQUIRE(array[0] == 0);
        REQUIRE(array[4] == 4);
    }

    WHEN("Replace") {
        auto* p = scope.Replace(1, 10);
        REQUIRE(p != nullptr);
        REQUIRE(*p == 10);
        REQUIRE(scope.GetNum() == 2);
        REQUIRE(scope[1] == 3);
        REQUIRE(scope[3] == 10);
        REQUIRE(array[1] == 3);
        REQUIRE(array[3] == 10);
    }
}

SCENARIO("OrderedObjectArray Slice Scope Append") {
    OrderedObjectArray<int, 10> array = {4,3,1,2};
    auto&& scope = array.From(0).Scope(0x0a);

    REQUIRE(scope.GetNum() == 2);

    WHEN("Append") {
        auto* p = scope.Append(0);
        REQUIRE(*p == 0);
        REQUIRE(scope.GetNum() == 2);
        REQUIRE(array[0] == 0);
        REQUIRE(array[4] == 4);
    }

    WHEN("Replace") {
        auto* p = scope.Replace(1, 10);
        REQUIRE(p != nullptr);
        REQUIRE(*p == 10);
        REQUIRE(scope.GetNum() == 2);
        REQUIRE(scope[1] == 3);
        REQUIRE(scope[3] == 10);
        REQUIRE(array[1] == 3);
        REQUIRE(array[3] == 10);
    }
}

namespace {
    int object_count = 0;

    struct Foo {
        int a;
        int b;
        explicit Foo(int a) : a{a}, b{a} {}
        explicit Foo(int a, int b) : a{a}, b{b} {}
        Foo(Foo const&) = default;
        auto operator=(Foo const&) -> Foo& = default;
        ~Foo() { a = 10; }
    };

    static_assert(!std::is_trivially_destructible_v<OrderedObjectArray<Foo, 10>>);

    auto FooLess = [](auto&& l, auto&& r) {
        return l.a < r.a;
    };
}

SCENARIO("Foo OrderedObjectArray") {
    OrderedObjectArray<Foo, 10, decltype(FooLess)> array;

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

SCENARIO("Foo Object OrderedObjectArray") {
    OrderedObjectArray<Foo, 10, decltype(FooLess)> array;

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

SCENARIO("Foo Object IndexOrderedArray with less compare") {
    using COMPARE = std::function<auto (Foo const&, Foo const&) -> bool>;
    OrderedObjectArray<Foo, 10, COMPARE> array{[](Foo const& l, Foo const& r) { return l.a < r.a; }};

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

SCENARIO("Foo Object IndexOrderedArray with Greater compare") {
    using COMPARE = std::function<auto (Foo const&, Foo const&) -> bool>;
    OrderedObjectArray<Foo, 10, COMPARE> array{[](Foo const& l, Foo const& r) { return l.a > r.a; }};

    array.Append(Foo{10});
    array.Append(Foo{8});
    array.Append(Foo{12});
    array.Append(Foo{7});
    array.Append(Foo{9});

    REQUIRE(array.GetNum() == 5);

    REQUIRE(array[0].a == 12);
    REQUIRE(array[1].a == 10);
    REQUIRE(array[2].a == 9);
    REQUIRE(array[3].a == 8);
    REQUIRE(array[4].a == 7);

    WHEN("Erase") {
        array.Erase(2);

        REQUIRE(array.GetNum() == 4);

        REQUIRE(array[0].a == 12);
        REQUIRE(array[1].a == 10);
        REQUIRE(array[2].a == 8);
        REQUIRE(array[3].a == 7);
    }

    WHEN("Clear") {
        array.Clear();
        REQUIRE(array.GetNum() == 0);
    }

    WHEN("Clear range") {
        array.Clear(1, 3);
        REQUIRE(array.GetNum() == 3);

        REQUIRE(array[0].a == 12);
        REQUIRE(array[1].a == 8);
        REQUIRE(array[2].a == 7);
    }

    WHEN("Clear from") {
        array.ClearFrom(2);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0].a == 12);
        REQUIRE(array[1].a == 10);
    }

    WHEN("Clear Until") {
        array.ClearUntil(3);
        REQUIRE(array.GetNum() == 2);

        REQUIRE(array[0].a == 8);
        REQUIRE(array[1].a == 7);
    }
}


SCENARIO("Foo Object IndexOrderedArray Range View") {
    using COMPARE = std::function<auto (Foo const&, Foo const&) -> bool>;
    OrderedObjectArray<Foo, 10, COMPARE> array{[](Foo const& l, Foo const& r) { return l.a > r.a; }};

    array.Append(Foo{10});
    array.Append(Foo{8, 3});
    array.Append(Foo{12});
    array.Append(Foo{8, 1});
    array.Append(Foo{7});
    array.Append(Foo{8, 5});
    array.Append(Foo{9});

    REQUIRE(array.GetNum() == 7);

    REQUIRE(array[0].a == 12);
    REQUIRE(array[1].a == 10);
    REQUIRE(array[2].a == 9);
    REQUIRE(array[3].a == 8);
    REQUIRE(array[4].a == 8);
    REQUIRE(array[5].a == 8);
    REQUIRE(array[6].a == 7);

    auto&& view = array.Range(Foo{8});
    REQUIRE(view.GetNum() == 3);
    REQUIRE(view[0].a == 8);
    REQUIRE(view[1].a == 8);
    REQUIRE(view[2].a == 8);

    WHEN("Sort") {
        view.Sort([](auto&& l, auto r) {
            return l.b < r.b;
        });

        REQUIRE(view.GetNum() == 3);
        REQUIRE(view[0].b == 1);
        REQUIRE(view[1].b == 3);
        REQUIRE(view[2].b == 5);
        REQUIRE(view[0].a == 8);
        REQUIRE(view[1].a == 8);
        REQUIRE(view[2].a == 8);
    }

    WHEN("SortObject") {
        auto&& sorted = view.SortObject().Sort([](auto&& l, auto r) {
            return l.b < r.b;
        });

        REQUIRE(sorted.GetNum() == 3);
        REQUIRE(sorted[0].b == 1);
        REQUIRE(sorted[1].b == 3);
        REQUIRE(sorted[2].b == 5);
        REQUIRE(sorted[0].a == 8);
        REQUIRE(sorted[1].a == 8);
        REQUIRE(sorted[2].a == 8);
    }
}

