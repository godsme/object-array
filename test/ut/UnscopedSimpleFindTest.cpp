//
// Created by Darwin Yuan on 2021/6/20.
//

#include <object-array/mixin/NonScopedSimpleFind.h>
#include <object-array/mixin/RangedArrayLike.h>
#include "Foo.h"
#include <catch.hpp>

namespace {
    struct FooArray : mixin::NonScopedSimpleFind<mixin::RangedArrayLike<ut::Foo>>, ut::Foo {
        using MixinUnderTest = mixin::NonScopedSimpleFind<mixin::RangedArrayLike<ut::Foo>>;
        using MixinUnderTest::Find;
        using MixinUnderTest::FindIndex;
        static_assert(std::is_empty_v<MixinUnderTest>);

    private:
        static auto __CheckSelf__() {
            static_assert(sizeof(FooArray) == sizeof(ut::Foo));
        }
    };

}

SCENARIO("NonScopedSimpleFind") {
    static_assert(sizeof(std::is_empty_v<mixin::NonScopedSimpleFind<mixin::RangedArrayLike<ut::Foo>>>) == 1);
    FooArray foo;
    foo.elems[0] = 2;
    foo.elems[1] = 6;
    foo.elems[2] = 3;
    foo.num = 3;

    WHEN("find index of an existing elem") {
        auto found = foo.FindIndex([](auto&& elem) {
            return elem == 6;
        });
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("find an existing elem") {
        auto* found = foo.Find([](auto&& elem) {
            return elem == 6;
        });
        REQUIRE(found != nullptr);
        REQUIRE(*found == 6);
    }

    WHEN("find an existing elem with index") {
        auto found = foo.FindIndex([](auto&& elem, auto n) {
            return elem == 6 && n == 1;
        });
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("find a non-existing elem") {
        auto found = foo.FindIndex([](auto&& elem) {
            return elem == 7;
        });
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("find a non-existing elem with index") {
        auto found = foo.FindIndex([](auto&& elem, auto index) {
            return elem == 6 && index != 1;
        });
        REQUIRE_FALSE(found.has_value());
    }

}