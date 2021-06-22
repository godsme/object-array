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
    Foo foo{{1,2,3,4}, 4};

    WHEN("r-value find an existing elem") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,2).FindIndex(2);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("r-value find an existing elem with Scope") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,2).Scope(0xFF).FindIndex(2);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
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