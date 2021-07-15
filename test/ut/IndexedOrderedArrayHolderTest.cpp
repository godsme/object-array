//
// Created by Darwin Yuan on 2021/7/9.
//
#include <l0-infra/array/IndexedOrderedArray.h>
#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

namespace {
    using IndexedArray = IndexedOrderedArray<int, 10>;
}

SCENARIO("IndexedOrderedArray Append") {
    IndexedArray array{};
    array.Append(10);
    array.Append(1);
    array.Append(8);
    array.Append(3);
    array.Append(5);

    REQUIRE(array.GetNum() == 5);
    REQUIRE(array[0] == 1);
    REQUIRE(array[1] == 3);
    REQUIRE(array[2] == 5);
    REQUIRE(array[3] == 8);
    REQUIRE(array[4] == 10);
}

namespace {
    struct Foo {
        Foo(int a, int b) : a{a}, b{b} {}

        int a;
        int b;
    };

    template<typename T>
    using MyLess = std::function<auto (T const&, T const&) -> bool>;

    using IndexedOrderedFooArray = indexed_ordered_array::Array<ObjectArray<Foo, 10>, MyLess<Foo>>;
}

SCENARIO("IndexedOrderedFooArray") {
    bool cond = true;
    IndexedOrderedFooArray array{[cond](auto&& l, auto&& r) {
        return cond ? (l.a < r.a) : (l.b < r.b);
    }};

    array.Append(Foo{2,2});
    array.Append(Foo{3,9});
    array.Append(Foo{2,7});
    array.Append(Foo{4,7});
    array.Append(Foo{3,1});
    array.Append(Foo{2,5});

    REQUIRE(array.GetNum() == 6);
    REQUIRE(array[0].a == 2);
    REQUIRE(array[1].a == 2);
    REQUIRE(array[2].a == 2);
    REQUIRE(array[3].a == 3);
    REQUIRE(array[4].a == 3);
    REQUIRE(array[5].a == 4);

    REQUIRE(array[0].b == 2);
    REQUIRE(array[1].b == 7);
    REQUIRE(array[2].b == 5);

    REQUIRE(array[3].b == 9);
    REQUIRE(array[4].b == 1);

//    WHEN("Range Sort") {
//        array.Unsafe_RangeSort(3, 5, [](Foo const& l, Foo const& r) {
//            return l.b < r.b;
//        });
//
//        REQUIRE(array[0].b == 2);
//        REQUIRE(array[1].b == 7);
//        REQUIRE(array[2].b == 5);
//
//        REQUIRE(array[3].b == 1);
//        REQUIRE(array[4].b == 9);
//    }

//    WHEN("Range ForEach") {
//        array.template RangeForEach<true>(2, 5, [](Foo& foo) {
//           foo.a += 10;
//        });
//
//        REQUIRE(array[0].a == 2);
//        REQUIRE(array[1].a == 2);
//        REQUIRE(array[2].a == 12);
//        REQUIRE(array[3].a == 13);
//        REQUIRE(array[4].a == 13);
//        REQUIRE(array[5].a == 4);
//    }
//
//    WHEN("Range ForEach i ") {
//        array.template RangeForEach<true>(2, 5, [](Foo& foo, auto i) {
//            foo.a += i;
//        });
//
//        REQUIRE(array[0].a == 2);
//        REQUIRE(array[1].a == 2);
//        REQUIRE(array[2].a == 2 + 2);
//        REQUIRE(array[3].a == 3 + 3);
//        REQUIRE(array[4].a == 3 + 4);
//        REQUIRE(array[5].a == 4);
//    }
}
