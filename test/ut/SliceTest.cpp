//
// Created by Darwin Yuan on 2021/6/22.
//

#include <object-array/view/Slice.h>
#include "Foo.h"
#include <catch.hpp>

SCENARIO("SliceTest") {
    ut::Foo foo;
    foo.elems[0] = 1;
    foo.elems[1] = 2;
    foo.elems[2] = 3;
    foo.elems[3] = 4;
    foo.elems[4] = 5;
    foo.elems[5] = 6;
    foo.elems[6] = 7;
    foo.num = 7;

    view::Slice<ut::Foo> slice{foo, 2, 5};

    WHEN("find an existing elem") {
        auto found = slice.FindIndex(5);
        REQUIRE(found.has_value());
        REQUIRE(*found == 4);
    }

    WHEN("find a non-existing elem") {
        auto found = slice.FindIndex(7);
        REQUIRE_FALSE(found);
    }

}

