//
// Created by Darwin Yuan on 2021/6/21.
//

#include <object-array/ObjectArray.h>
#include <catch.hpp>

SCENARIO("Int ObjectArray") {
    using IntArray = ObjectArray<int, 5>;
    IntArray foo;

    foo.Elems()[0] = 2;
    foo.Elems()[1] = 6;
    foo.Elems()[2] = 3;
    foo.Num() = 3;

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

namespace {

//    struct Array : holder::ObjectArrayHolder<int, 5>
//            , mixin::NonScopedSimpleFind<mixin::RangedArrayLike<holder::ObjectArrayHolder<int, 5>>> {
//
//    };
}