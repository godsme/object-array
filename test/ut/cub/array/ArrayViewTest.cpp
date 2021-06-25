//
// Created by Darwin Yuan on 2021/6/22.
//

#include <object-array/ArrayView.h>
#include <catch.hpp>

namespace {
    struct Foo {
        int array[10];
        uint8_t num;
    };
}

SCENARIO("ArrayView Test") {
    Foo foo{{1,2,3,4,5,6,7,8}, 8};

    {
        ArrayView lvalueView{foo.array, foo.num};
        static_assert(sizeof(decltype(ArrayView{foo.array, foo.num}.Slice(1,2)))
                      > sizeof(decltype(lvalueView.Slice(1,2))));

        static_assert(sizeof(decltype(ArrayView{foo.array, foo.num}.Slice(1,2).Scope(0xFF)))
                      > sizeof(decltype(lvalueView.Slice(1,2).Scope(0xFF))));
    }


    WHEN("r-value find an existing elem") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,2).FindIndex(2);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("r-value find an existing elem with Scope") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,6).Scope(0xF0).FindIndex(5);
        REQUIRE(found.has_value());
        REQUIRE(*found == 4);
    }

    WHEN("r-value find a non-existing elem with Scope") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,6).Scope(0xF0).FindIndex(1);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("r-value find another non-existing elem with Scope") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,6).Scope(0xF0).FindIndex(8);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("l-value find a non-existing elem with Scope") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,6).Scope(0xF0).FindIndex(1);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("l-value find another non-existing elem with Scope") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,6).Scope(0xF0).FindIndex(8);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("r-value find a non-existing elem") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,2).FindIndex(4);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("l-value find an existing elem") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,2).FindIndex(2);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("l-value find a non-existing elem") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,2).FindIndex(4);
        REQUIRE_FALSE(found.has_value());
    }
}