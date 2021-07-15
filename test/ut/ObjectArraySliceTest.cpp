//
// Created by Darwin Yuan on 2021/7/11.
//

#include <l0-infra/array/ObjectArray.h>
#include <l0-infra/array/view/SliceView.h>
#include <catch.hpp>

SCENARIO("Slice ForEach") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array{10, 7, 8, 1, 4};
    RefSliceView<ArrayType> view{array, 1, 4};

    static_assert(!ArrayType::IS_ORDERED);

    REQUIRE(view.GetNum() == 3);
    REQUIRE(view[0] == 7);

    WHEN("ForEach") {
        auto n = 0;
        auto sum = 0;
        view.ForEach([&](auto&& elem) {
            n++;
            sum += elem;
        });
        REQUIRE(n == 3);
        REQUIRE(sum == 7 + 8 + 1);
    }

    WHEN("MinElemIndex") {
        auto index = view.MinElemIndex();
        REQUIRE(index.has_value());
        REQUIRE(*index == 3);
        REQUIRE(array[*index] == 1);
    }

    WHEN("MinElem") {
        auto* p = view.MinElem();
        REQUIRE(p != nullptr);
        REQUIRE(*p == 1);
    }

    WHEN("PartialSort") {
        auto&& sorted = view.PartialSort(std::less<int>{}, 2);
        REQUIRE(sorted.GetNum() == 2);
        REQUIRE(sorted[0] == 1);
        REQUIRE(sorted[1] == 7);

        REQUIRE(view.GetNum() == 3);
        REQUIRE(view[0] == 1);
        REQUIRE(view[1] == 7);
        REQUIRE(view[2] == 8);
    }

    WHEN("PartialSort 1") {
        auto&& sorted = view.PartialSort(2);
        REQUIRE(sorted.GetNum() == 2);
        REQUIRE(sorted[0] == 1);
        REQUIRE(sorted[1] == 7);

        REQUIRE(view.GetNum() == 3);
        REQUIRE(view[0] == 1);
        REQUIRE(view[1] == 7);
        REQUIRE(view[2] == 8);
    }
}
