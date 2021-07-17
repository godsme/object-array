//
// Created by Darwin Yuan on 2021/7/10.
//

#include <l0-infra/array/view/SortView.h>
#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

SCENARIO("Value SortView") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    SortView::ValueView<ArrayType> view{array};
    REQUIRE(array.GetNum() == 0);
    REQUIRE(view.GetNum() == 0);

    auto&& sorted = view.Sort(std::less<int>{});
    REQUIRE(view.GetNum() == 5);
    REQUIRE(sorted.GetNum() == 5);
    REQUIRE(sorted[0] == 2);
    REQUIRE(sorted[1] == 3);
    REQUIRE(sorted[2] == 6);
    REQUIRE(sorted[3] == 8);
    REQUIRE(sorted[4] == 9);
}

SCENARIO("Ref SortView") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    SortView::RefView<ArrayType> view{array};
    REQUIRE(array.GetNum() == 5);
    REQUIRE(view.GetNum() == 0);

    auto&& sorted = view.Sort(std::less<int>{});
    REQUIRE(view.GetNum() == 5);
    REQUIRE(sorted.GetNum() == 5);
    REQUIRE(sorted[0] == 2);
    REQUIRE(sorted[1] == 3);
    REQUIRE(sorted[2] == 6);
    REQUIRE(sorted[3] == 8);
    REQUIRE(sorted[4] == 9);
}

SCENARIO("r-Value SortView") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    {
        auto&& sorted = SortView::ValueView<ArrayType>{array}.Sort(std::less<int>{});
        REQUIRE(sorted.GetNum() == 5);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 3);
        REQUIRE(sorted[2] == 6);
        REQUIRE(sorted[3] == 8);
        REQUIRE(sorted[4] == 9);
    }
}

SCENARIO("r-Value StableSortView") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    {
        auto&& sorted = SortView::ValueView<ArrayType>{array}.StableSort(std::less<int>{});
        REQUIRE(sorted.GetNum() == 5);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 3);
        REQUIRE(sorted[2] == 6);
        REQUIRE(sorted[3] == 8);
        REQUIRE(sorted[4] == 9);
    }
}

SCENARIO("r-Value SortView MinElems") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    {
        auto&& sorted = SortView::ValueView<ArrayType>{array}.MinElems(std::less<int>{}, 2);
        REQUIRE(sorted.GetNum() == 2);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 3);
    }
}

SCENARIO("l-Value SortView MinElems") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    SortView::ValueView<ArrayType> view{array};
    REQUIRE(view.GetNum() == 0);

    {
        auto&& sorted = view.MinElems(std::less<int>{}, 2);
        REQUIRE(sorted.GetNum() == 2);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 3);
    }
}

SCENARIO("l-Value SortView MinElems 1") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    SortView::ValueView<ArrayType> view{array};
    REQUIRE(view.GetNum() == 0);

    {
        auto&& sorted = view.MinElems(std::less<int>{}, 1);
        REQUIRE(sorted.GetNum() == 1);
        REQUIRE(sorted[0] == 2);
    }
}

SCENARIO("l-Value SortView range for") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    SortView::ValueView<ArrayType> view{array};
    REQUIRE(view.GetNum() == 0);

    {
        auto&& sorted = view.MinElems(std::less<int>{}, 10);
        int indices[10]{};
        int n = 0;
        for(auto&& [elem, i] : sorted.WithIndex()) {
            indices[n++] = i;
        }

        REQUIRE(n == 5);
        REQUIRE(indices[0] == 3);
        REQUIRE(indices[1] == 1);
        REQUIRE(indices[2] == 2);
        REQUIRE(indices[3] == 4);
        REQUIRE(indices[4] == 0);
    }

    {
        auto&& sorted = view.MinElems(std::less<int>{}, 10);
        int indices[10]{};
        int n = 0;
        for(auto&& [elem, i] : sorted.Enumerate()) {
            indices[n++] = i;
        }

        REQUIRE(n == 5);
        REQUIRE(indices[0] == 0);
        REQUIRE(indices[1] == 1);
        REQUIRE(indices[2] == 2);
        REQUIRE(indices[3] == 3);
        REQUIRE(indices[4] == 4);
    }
}

SCENARIO("l-Value SortView MinElems 0") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array {9, 3, 6, 2, 8};
    REQUIRE(array.GetNum() == 5);

    SortView::ValueView<ArrayType> view{array};
    REQUIRE(view.GetNum() == 0);

    {
        auto&& sorted = view.MinElems(std::less<int>{}, 1);
        REQUIRE(sorted.GetNum() == 1);
        REQUIRE(sorted[0] == 2);

        auto&& sorted2 = view.MinElems(std::less<int>{}, 0);
        REQUIRE(sorted.GetNum() == 0);
    }
}

