//
// Created by Darwin Yuan on 2021/6/26.
//

#include <l0-infra/array/view/SortView.h>
#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

SCENARIO("SortView Test") {
    using Array = ObjectArray<int, 90>;
    Array array{3,2,4,1};

    WHEN("array itself should be able to sort") {
        array.Sort();
        REQUIRE(array[0] == 1);
        REQUIRE(array[1] == 2);
        REQUIRE(array[2] == 3);
        REQUIRE(array[3] == 4);
    }

    WHEN("should be able to sort by sort object") {
        auto&& sorted = array.SortObject();

        sorted.Sort();

        REQUIRE(sorted[0] == 1);
        REQUIRE(sorted[1] == 2);
        REQUIRE(sorted[2] == 3);
        REQUIRE(sorted[3] == 4);

        REQUIRE(array[0] == 3);
        REQUIRE(array[1] == 2);
        REQUIRE(array[2] == 4);
        REQUIRE(array[3] == 1);
    }

    WHEN("should be able to sort by sort object") {
        auto&& sorted = array.SortObject();

        int a[10];
        int n = 0;
        for(auto&& elem : sorted.Sort()) {
            a[n++] = elem;
        }

        REQUIRE(n == 4);
        REQUIRE(a[0] == 1);
        REQUIRE(a[1] == 2);
        REQUIRE(a[2] == 3);
        REQUIRE(a[3] == 4);
    }

    WHEN("Create a sort view on Slice") {
        auto&& view = array.From(1).SortObject().Sort();

        REQUIRE(view[0] == 1);
        REQUIRE(view[1] == 2);
        REQUIRE(view[2] == 4);
    }

    WHEN("Create a sort view on scoped view") {
        auto&& view = array.Scope(0x0a).SortObject().Sort();

        REQUIRE(view[0] == 1);
        REQUIRE(view[1] == 2);
    }

    WHEN("Create a sort view on scoped view") {
        auto&& view = array.Scope(0x0a).SortObject().PartialSort(2);

        REQUIRE(view[0] == 1);
        REQUIRE(view[1] == 2);
    }

    WHEN("Scope view should be able to sort directly") {
        auto&& view = array.Scope(0x0a).Sort();
        REQUIRE(view[0] == 3);
        REQUIRE(view[1] == 1);
        REQUIRE(view[2] == 4);
        REQUIRE(view[3] == 2);

        REQUIRE(!view.IsPresent(0));
        REQUIRE(view.IsPresent(1));
        REQUIRE(!view.IsPresent(2));
        REQUIRE(view.IsPresent(3));

        REQUIRE(array[0] == 3);
        REQUIRE(array[1] == 1);
        REQUIRE(array[2] == 4);
        REQUIRE(array[3] == 2);
    }
}