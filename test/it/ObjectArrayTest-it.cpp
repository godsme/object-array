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

suite ObjectArraySimpleFind_Suite = [] {
    FooArray array{{1},{2},{3},{4},{5},{6}};

    "should be able to find the index of an existent elem"_test = [&] {
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
};