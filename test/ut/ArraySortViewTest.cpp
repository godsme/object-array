//
// Created by Darwin Yuan on 2021/7/12.
//

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
        auto&& sorted = array.SortView();

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

    WHEN("ranged sort") {
        auto&& sorted = array.SortView();

        int a[10];
        int n = 0;
        for(auto&& elem : sorted.Sort()) {
            a[n++] = elem;
        }

        REQUIRE(n == 4);
        CHECK(a[0] == 1);
        CHECK(a[1] == 2);
        CHECK(a[2] == 3);
        CHECK(a[3] == 4);
    }

    WHEN("SortView Find") {
        auto&& sorted = array.SortView();
        REQUIRE(sorted.GetNum() == 0);
        sorted.Sort();
        REQUIRE(sorted.GetNum() == 4);

        auto index = sorted.FindIndex(2);
        REQUIRE(index.has_value());
        REQUIRE(*index == 1);
    }

    WHEN("ranged sort with index") {
        auto&& sorted = array.SortView();

        uint8_t indices[10];
        int a[10];
        int n = 0;
        for(auto&& [elem, i] : sorted.Sort().WithIndex()) {
            indices[n] = i;
            a[n++] = elem;
        }

        REQUIRE(n == 4);
        CHECK(a[0] == 1);
        CHECK(a[1] == 2);
        CHECK(a[2] == 3);
        CHECK(a[3] == 4);

        CHECK(indices[0] == 3);
        CHECK(indices[1] == 1);
        CHECK(indices[2] == 0);
        CHECK(indices[3] == 2);
    }

    WHEN("Create a sort view on Slice") {
        auto&& view = array.From(1).SortView().Sort();

        REQUIRE(view[0] == 1);
        REQUIRE(view[1] == 2);
        REQUIRE(view[2] == 4);
    }

    WHEN("Create a sort view on scoped view") {
        auto&& view = array.Scope(0x0a).SortView().Sort();

        REQUIRE(view[0] == 1);
        REQUIRE(view[1] == 2);
    }

    WHEN("Create a sort view on scoped view") {
        auto&& view = array.Scope(0x0a).SortView().PartialSort(2);

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