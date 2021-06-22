//
// Created by Darwin Yuan on 2021/6/20.
//
#include <object-array/mixin/SimpleFindExt.h>
#include <object-array/mixin/NonScopedSimpleFind.h>
#include <catch.hpp>
#include <object-array/mixin/RangedArrayLike.h>
#include "Foo.h"

namespace {
    struct FooArray : ut::Foo, mixin::SimpleFindExt<mixin::NonScopedSimpleFind<mixin::RangedArrayLike<ut::Foo>>> {
        using MixinUnderTest = mixin::SimpleFindExt<mixin::NonScopedSimpleFind<mixin::RangedArrayLike<ut::Foo>>>;
        using MixinUnderTest::FindIndex;
        using MixinUnderTest::Find;
        static_assert(std::is_empty_v<MixinUnderTest>);
    };
}

SCENARIO("SimpleFindExt") {
    FooArray foo;
    foo.elems[0] = 2;
    foo.elems[1] = 6;
    foo.elems[2] = 3;
    foo.num = 3;
    WHEN("find an existing elem") {
        auto found = foo.FindIndex(6);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("find an existing elem with index") {
        REQUIRE_FALSE(foo.FindIndex(7).has_value());
    }
}
