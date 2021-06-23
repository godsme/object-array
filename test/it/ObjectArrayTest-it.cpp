//
// Created by Darwin Yuan on 2021/6/23.
//
#include <object-array/ObjectArray.h>
#include <boost/ut.hpp>

using namespace boost::ut;

namespace {
    struct Foo {
        Foo(int a) : a{a} {}
        Foo(Foo const&) = default;
        ~Foo() {}

        auto operator==(Foo const&) const -> bool = default;

        int a;
    };

    using FooArray = ObjectArray<Foo, 10>;
}

template<typename ARRAY>
auto SimpleFindTest(ARRAY&& array) {
    test("should be able to find the index of an existent elem") = [&] {
        auto found = array.FindIndex(Foo{3});
        expect(found.has_value());
        expect(*found == 2);
    };

    "should be able to find an existent elem"_test = [&] {
        auto* found = array.Find(Foo{3});
        expect(found != nullptr);
        expect(*found == 3);
    };

    "should return nullptr if trying to find a non-existent elem"_test = [&] {
        expect(nullptr == array.Find(Foo{0}));
    };

    "should be able to find the index of an existent elem by predicate"_test = [&] {
        auto found = array.FindIndex([](auto&& elem) {
            return elem == 3;
        });
        expect(found.has_value());
        expect(*found == 2);
    };

    "should be able to find an existent elem by predicate"_test = [&] {
        auto* found = array.Find([](auto&& elem) {
            return elem == 5;
        });
        expect(found != nullptr);
        expect(*found == 5);
    };

    "should return nullptr if trying to find a non-existent elem by predicate"_test = [&] {
        expect(nullptr == array.Find([](auto&& elem) {
            return elem == 10;
        }));
    };

    "should return std::nullopt if trying to find the index of a non-existent elem"_test = [&] {
        expect(array.FindIndex(Foo{0}) == std::nullopt);
    };

    "should return std::nullopt if trying to find the index of a non-existent elem by predicate"_test = [&] {
        expect(std::nullopt == array.FindIndex([](auto&& elem) { return elem.a == 0; }));
    };

    "should be able to know the existence of an elem"_test = [&] {
        expect(array.Exists(5));
        expect(!array.Exists(10));
    };
}

suite ObjectArraySimpleFind_Suite = [] {
    FooArray const array{{1},{2},{3},{4},{5},{6}};
    SimpleFindTest(array);

    SimpleFindTest(FooArray{{1},{2},{3},{4},{5},{6}});
};

template<typename ARRAY>
auto RangeForTest(ARRAY&& array) {
    "should be able to iterator all items"_test = [&] {
        auto n=0;
        auto sum = 0;
        for(auto&& item : array) {
            ++n;
            sum += item.a;
        }

        expect(n == 6);
        expect(sum == (1 + 2 + 3 + 4 + 5 + 6));
    };

    "should be able to iterator all items with index"_test = [&] {
        auto n=0;
        auto sum = 0;
        for(auto&& [item, i] : array.WithIndex()) {
            expect(n == i);
            ++n;
            sum += item.a;
        }

        expect(n == 6);
        expect(sum == (1 + 2 + 3 + 4 + 5 + 6));
    };

    "range for index should not be able to modify"_test = [&] {
        for(auto&& [item, i] : array.WithIndex()) {
            static_assert(std::is_const_v<decltype(i)>);
        }
    };

    "range for index should not be able to modify if array is const"_test = [&] {
        if constexpr(std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& [item, i] : array.WithIndex()) {
                static_assert(std::is_reference_v<decltype(item)>);
                static_assert(std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };

    "range for index should be able to modify if array is not const"_test = [&] {
        if constexpr(!std::is_const_v<std::remove_reference_t<decltype(array)>>) {
            for(auto&& [item, i] : array.WithIndex()) {
                static_assert(std::is_reference_v<decltype(item)>);
                expect(!std::is_const_v<std::remove_reference_t<decltype(item)>>);
            }
        }
    };
}

suite ObjectArrayRangeFor_Suite = [] {
    FooArray const array{{1},{2},{3},{4},{5},{6}};
    RangeForTest(array);

    RangeForTest(FooArray{{1},{2},{3},{4},{5},{6}});
};
