//
// Created by Darwin Yuan on 2021/7/11.
//

#include <l0-infra/array/ObjectArray.h>
#include <l0-infra/array/view/ScopeView.h>
#include <catch.hpp>
#include <iostream>

SCENARIO("ScopeView") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array{10, 7, 8, 1, 5, 2, 4};
    RefScopeView<ArrayType> view{array, 0x35}; // 110101 (10, 8, 5, 2)

    REQUIRE(view.GetNum() == 4);
    REQUIRE(view.IndexBegin() == 0);
    REQUIRE(view.IndexEnd() == 7);

    WHEN("ForEach") {
        auto n = 0;
        auto sum = 0;
        view.ForEach([&](auto&& elem) {
            n++;
            sum += elem;
        });
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
    }

    WHEN("ForEach with index") {
        auto n = 0;
        auto sum = 0;
        int indices[10] = {};
        view.ForEach([&](auto&& elem, auto i) {
            indices[n] = i;
            n++;
            sum += elem;
        });
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
        REQUIRE(indices[0] == 0);
        REQUIRE(indices[1] == 2);
        REQUIRE(indices[2] == 4);
        REQUIRE(indices[3] == 5);
    }

    WHEN("Range For") {
        auto n = 0;
        auto sum = 0;
        for(auto&& elem : view) {
            n++;
            sum += elem;
        };
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
    }

    WHEN("Range For WithIndex") {
        auto n = 0;
        auto sum = 0;
        int indices[10] = {};
        for(auto&& [elem, i] : view.WithIndex()) {
            indices[n] = i;
            n++;
            sum += elem;
        };
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
        REQUIRE(indices[0] == 0);
        REQUIRE(indices[1] == 2);
        REQUIRE(indices[2] == 4);
        REQUIRE(indices[3] == 5);
    }

    WHEN("MinElemIndex") {
        auto index = view.MinElemIndex();
        REQUIRE(index.has_value());
        REQUIRE(*index == 5);
        REQUIRE(array[*index] == 2);
    }

    WHEN("MinElem") {
        auto* p = view.MinElem();
        REQUIRE(p != nullptr);
        REQUIRE(*p == 2);
    }

    WHEN("FindIndex") {
        auto index = view.FindIndex(8);
        REQUIRE(index.has_value());
        REQUIRE(*index == 2);
    }

    WHEN("Find") {
        auto* p = view.Find(8);
        REQUIRE(p != nullptr);
        REQUIRE(*p == 8);
    }

    WHEN("PartialSort") {
        auto&& sorted = view.PartialSort(std::less<int>{}, 2);
        REQUIRE(sorted.GetNum() == 2);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 7);
        REQUIRE(sorted[2] == 5);

        REQUIRE(view.GetNum() == 4);
        REQUIRE(view[0] == 2);
        REQUIRE(view[1] == 7);
        REQUIRE(view[2] == 5);
        REQUIRE(view[3] == 1);
        REQUIRE(view[4] == 10);
        REQUIRE(view[5] == 8);
        REQUIRE(view[6] == 4);
    }

    WHEN("Sort") {
        auto&& sorted = view.Sort(std::less<int>{});
        REQUIRE(sorted.GetNum() == 4);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 7);
        REQUIRE(sorted[2] == 5);
        REQUIRE(sorted[3] == 1);
        REQUIRE(sorted[4] == 8);
        REQUIRE(sorted[5] == 10);
        REQUIRE(sorted[6] == 4);

        REQUIRE(view.GetNum() == 4);
        REQUIRE(view[0] == 2);
        REQUIRE(view[1] == 7);
        REQUIRE(view[2] == 5);
        REQUIRE(view[3] == 1);
        REQUIRE(view[4] == 8);
        REQUIRE(view[5] == 10);
        REQUIRE(view[6] == 4);
    }
}

SCENARIO("Range ScopeView") {
    using ArrayType = ObjectArray<int, 10>;
    ArrayType array{12, 10, 7, 8, 1, 5, 2, 4, 3};
    auto&& slice = array.Slice(1,-1);
    ArrayType::BitMap scope;
    scope.set(1);
    scope.set(3);
    scope.set(5);
    scope.set(6);

    RefScopeView<std::decay_t<decltype(array.Slice(1,-1))>> view{slice, scope}; // 110101 (10, 8, 5, 2)

    REQUIRE(view.GetNum() == 4);
    REQUIRE(view.IndexBegin() == 1);
    REQUIRE(view.IndexEnd() == 8);
    REQUIRE(view.GetObject(0) == 12);

    WHEN("ForEach") {
        auto n = 0;
        auto sum = 0;
        view.ForEach([&](auto&& elem) {
            n++;
            sum += elem;
        });
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
    }

    WHEN("ForEach with index") {
        auto n = 0;
        auto sum = 0;
        int indices[10] = {};
        view.ForEach([&](auto&& elem, auto i) {
            indices[n] = i;
            n++;
            sum += elem;
        });
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
        REQUIRE(indices[0] == 1);
        REQUIRE(indices[1] == 3);
        REQUIRE(indices[2] == 5);
        REQUIRE(indices[3] == 6);
    }

    WHEN("Range For") {
        auto n = 0;
        auto sum = 0;
        for(auto&& elem : view) {
            n++;
            sum += elem;
        };
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
    }

    WHEN("Range For WithIndex") {
        auto n = 0;
        auto sum = 0;
        int indices[10] = {};
        for(auto&& [elem, i] : view.WithIndex()) {
            indices[n] = i;
            n++;
            sum += elem;
        };
        REQUIRE(n == 4);
        REQUIRE(sum == 10 + 8 + 5 + 2);
        REQUIRE(indices[0] == 1);
        REQUIRE(indices[1] == 3);
        REQUIRE(indices[2] == 5);
        REQUIRE(indices[3] == 6);
    }

    WHEN("MinElemIndex") {
        auto index = view.MinElemIndex();
        REQUIRE(index.has_value());
        REQUIRE(*index == 6);
        REQUIRE(array[*index] == 2);
    }

    WHEN("MinElem") {
        auto* p = view.MinElem();
        REQUIRE(p != nullptr);
        REQUIRE(*p == 2);
    }

    WHEN("FindIndex") {
        auto index = view.FindIndex(8);
        REQUIRE(index.has_value());
        REQUIRE(*index == 3);
    }

    WHEN("Find") {
        auto* p = view.Find(8);
        REQUIRE(p != nullptr);
        REQUIRE(*p == 8);
    }

    WHEN("PartialSort") {
        auto&& sorted = view.PartialSort(std::less<int>{}, 2);
        REQUIRE(sorted.GetNum() == 2);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 7);
        REQUIRE(sorted[2] == 5);

        REQUIRE(view.GetNum() == 4);
        REQUIRE(view[0] == 2);
        REQUIRE(view[1] == 7);
        REQUIRE(view[2] == 5);
        REQUIRE(view[3] == 1);
        REQUIRE(view[4] == 10);
        REQUIRE(view[5] == 8);
        REQUIRE(view[6] == 4);
    }

    WHEN("Sort") {
        auto&& sorted = view.Sort(std::less<int>{});
        REQUIRE(sorted.GetNum() == 4);
        REQUIRE(sorted[0] == 2);
        REQUIRE(sorted[1] == 7);
        REQUIRE(sorted[2] == 5);
        REQUIRE(sorted[3] == 1);
        REQUIRE(sorted[4] == 8);
        REQUIRE(sorted[5] == 10);
        REQUIRE(sorted[6] == 4);

        REQUIRE(view.GetNum() == 4);
        REQUIRE(view[0] == 2);
        REQUIRE(view[1] == 7);
        REQUIRE(view[2] == 5);
        REQUIRE(view[3] == 1);
        REQUIRE(view[4] == 8);
        REQUIRE(view[5] == 10);
        REQUIRE(view[6] == 4);
    }

    WHEN("SortView") {
        auto&& elems = view.MinElems(2);
        REQUIRE(elems.GetNum() == 2);
        REQUIRE(elems[0] == 2);
        REQUIRE(elems[1] == 5);
    }
}