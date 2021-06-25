//
// Created by Darwin Yuan on 2021/6/25.
//
#include <l0-infra/array/ObjectArray.h>
#include <boost/ut.hpp>

using namespace boost::ut;

namespace {
    struct Foo {
        Foo(int a) : a{a} {}
        Foo(Foo const&) = default;
        auto operator=(Foo const&) -> Foo& = default;
        ~Foo() {}

        auto operator==(Foo const&) const -> bool = default;
        auto operator<(Foo const& rhs) const -> bool {
            return a < rhs.a;
        }

        int a;
    };

    using FooArray = ObjectArray<Foo, 10>;
}

suite SliceFind_Suite = [] {
    FooArray array{{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}};

    "the size of double zero slice should be 1"_test = [&] {
        auto&& slice = array.Slice(0, 0);
        expect(slice.GetNum() == 1);
        expect(*slice.At(0) == 0);
        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "the size of double end slice should be 1"_test = [&] {
        auto&& slice = array.Slice(8, 8);
        expect(slice.GetNum() == 1);
        expect(*slice.At(0) == 8);
        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "should be able to specify wrong boundary"_test = [&] {
        auto&& slice = array.Slice(-20, -10);
        expect(slice.GetNum() == 0);
        auto n = 0;
        for(auto&& elem : slice) {
            n++;
        }
        expect(n == 0);
        expect(slice.At(0) == nullptr);
        expect(!slice.Any());
        expect(slice.None());
        expect(!slice.All());
    };

    "should be able to specify wrong boundary to create an empty slice"_test = [&] {
        auto&& slice = array.Slice(10, 20);
        expect(slice.GetNum() == 0);
        auto n = 0;
        for(auto&& elem : slice) {
            n++;
        }
        expect(n == 0);
        expect(slice.At(0) == nullptr);
        expect(!slice.Any());
        expect(slice.None());
        expect(!slice.All());
    };

    "left boundary should be able to adjust to 0"_test = [&] {
        auto&& slice = array.Slice(-10, 0);
        expect(slice.GetNum() == 1);
        auto n = 0;
        for(auto&& elem : slice) {
            n++;
        }
        expect(n == 1);
        expect(*slice.At(0) == 0);
        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "left boundary should be able to adjust to 0"_test = [&] {
        auto&& slice = array.Until(-10);
        expect(slice.GetNum() == 0);
        auto n = 0;
        for(auto&& elem : slice) {
            n++;
        }
        expect(n == 0);
        expect(slice.At(0) == nullptr);
        expect(!slice.Any());
        expect(slice.None());
        expect(!slice.All());
    };

    "right boundary could be 0"_test = [&] {
        auto&& slice = array.Until(0);
        expect(slice.GetNum() == 1);
        auto n = 0;
        for(auto&& elem : slice) {
            n++;
        }
        expect(n == 1);
        expect(*slice.At(0) == 0);
        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "right boundary could be limited to right boundary"_test = [&] {
        auto&& slice = array.Until(100);
        expect(slice.GetNum() == 9);
        auto n = 0;
        auto sum = 0;
        for(auto&& elem : slice) {
            n++;
            sum += elem.a;
        }
        expect(n == 9);
        expect(sum == 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8);

        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "right boundary could be limited to right boundary"_test = [&] {
        auto&& slice = array.From(-10);
        expect(slice.GetNum() == 9);
        auto n = 0;
        auto sum = 0;
        for(auto&& elem : slice) {
            n++;
            sum += elem.a;
        }
        expect(n == 9);
        expect(sum == 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8);

        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "right boundary could be limited to right boundary"_test = [&] {
        auto&& slice = array.Until(-9);
        expect(slice.GetNum() == 1);
        auto n = 0;
        auto sum = 0;
        for(auto&& elem : slice) {
            n++;
            sum += elem.a;
        }
        expect(n == 1);
        expect(*slice.At(0) == 0);

        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "left boundary should be able to adjust to 0"_test = [&] {
        auto&& slice = array.Slice(8, 100);
        expect(slice.GetNum() == 1);
        auto n = 0;
        for(auto&& elem : slice) {
            n++;
        }
        expect(n == 1);
        expect(*slice.At(0) == 8);

        expect(slice.Any());
        expect(!slice.None());
        expect(!slice.All());
    };

    "should be able to sort"_test = [&] {
        auto&& slice = array.Slice(1, 3);

        slice.DescSort();

        expect(slice[0] == 3);
        expect(slice[1] == 2);
        expect(slice[2] == 1);
        expect(array[0] == 0);
        expect(array[4] == 4);

        slice.Sort();

        expect(slice[0] == 1);
        expect(slice[1] == 2);
        expect(slice[2] == 3);
    };

    "should be able to partial sort"_test = [&] {
        auto&& slice = array.Slice(1, 4);

        slice.PartialDescSort(2);

        expect(slice[0] == 4);
        expect(slice[1] == 3);
        expect(slice[2] == 1);
        expect(slice[3] == 2);

        expect(array[0] == 0);
        expect(array[5] == 5);

        slice.PartialSort(3);

        expect(slice[0] == 1);
        expect(slice[1] == 2);
        expect(slice[2] == 3);
        expect(slice[3] == 4);
    };

    "should be able to stable sort"_test = [&] {
        auto&& slice = array.Slice(1, 3);

        slice.StableDescSort();

        expect(slice[0] == 3);
        expect(slice[1] == 2);
        expect(slice[2] == 1);
        expect(array[0] == 0);
        expect(array[4] == 4);

        slice.StableSort();

        expect(slice[0] == 1);
        expect(slice[1] == 2);
        expect(slice[2] == 3);
    };
};