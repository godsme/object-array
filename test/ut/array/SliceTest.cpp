//
// Created by Darwin Yuan on 2021/6/22.
//

#include <l0-infra/array/view/Slice.h>
#include "../Foo.h"
#include <catch.hpp>

SCENARIO("SliceTest") {
    ut::Foo foo = {1,2,3,4,5,6,7};
    view::Slice<ut::Foo, false> slice{foo, 2, 5};

    REQUIRE(slice.GetNum() == 3);

    WHEN("find an existing elem") {
        auto found = slice.FindIndex(5);
        REQUIRE(found.has_value());
        REQUIRE(*found == 4);
    }

    WHEN("find a non-existing elem") {
        auto found = slice.FindIndex(7);
        REQUIRE_FALSE(found);
    }

    WHEN("replace an element") {
        auto* replaced = slice.Replace(0, 10);
        REQUIRE(replaced != nullptr);
    }

    WHEN("Append") {
        auto* elem = slice.Append(8);
        REQUIRE(elem != nullptr);
        REQUIRE(*elem == 8);
        REQUIRE(slice.GetNum() == 3);

        REQUIRE(slice.Append(9) != nullptr);
        REQUIRE(slice.GetNum() == 3);
        REQUIRE(slice.Append(10) != nullptr);
        REQUIRE(slice.GetNum() == 3);
        REQUIRE(slice.Append(11) == nullptr);
        REQUIRE(slice.GetNum() == 3);
    }
}

SCENARIO("FromSlice Test") {
    ut::Foo foo = {1,2,3,4,5,6,7};
    view::FromView<ut::Foo, false> slice{foo, 2};

    REQUIRE(slice.GetNum() == 5);

    WHEN("Append") {
        auto* elem = slice.Append(8);
        REQUIRE(elem != nullptr);
        REQUIRE(*elem == 8);
        REQUIRE(slice.GetNum() == 6);
    }
}

