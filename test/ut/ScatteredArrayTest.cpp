//
// Created by Darwin Yuan on 2021/6/22.
//

#include <object-array/ScatteredArray.h>
#include <catch.hpp>

SCENARIO("ScatteredArray Test") {
    ScatteredArray<int, 10> foo {2, 6, 3};

    WHEN("find index of an existing elem") {
        auto found = foo.FindIndex([](auto&& elem) {
            return elem == 6;
        });
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("find an existing elem") {
        auto* found = foo.Find([](auto&& elem) {
            return elem == 6;
        });
        REQUIRE(found != nullptr);
        REQUIRE(*found == 6);
    }

    WHEN("find an existing elem with index") {
        auto found = foo.FindIndex([](auto&& elem, auto n) {
            return elem == 6 && n == 1;
        });
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("find a non-existing elem") {
        auto found = foo.FindIndex([](auto&& elem) {
            return elem == 7;
        });
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("find a non-existing elem with index") {
        auto found = foo.FindIndex([](auto&& elem, auto index) {
            return elem == 6 && index != 1;
        });
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("find an existing object") {
        auto found = foo.FindIndex(6);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("find an existing object with index") {
        REQUIRE_FALSE(foo.FindIndex(7).has_value());
    }
}