//
// Created by Darwin Yuan on 2021/6/20.
//

#include <object-array/mixin/UnscopedSimpleFind.h>
#include <catch.hpp>

namespace {
    struct Foo {
        int elems[10];
        std::size_t num{};

        using SizeType = std::size_t;
        using ObjectType = int;
        using ElemType = int;

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return num; }
        auto GetObj(SizeType n) const -> ObjectType const& { return elems[n]; }
    };

    struct FooArray : Foo, mixin::UnscopedSimpleFind<Foo> {
        using mixin::UnscopedSimpleFind<Foo>::FindIndex;
        static_assert(std::is_empty_v<mixin::UnscopedSimpleFind<Foo>>);
    };
}

SCENARIO("UnscopedSimpleFind") {
    FooArray foo;
    foo.elems[0] = 2;
    foo.elems[1] = 6;
    foo.elems[2] = 3;
    foo.num = 3;

    WHEN("find an existing elem") {
        auto found = foo.FindIndex([](auto&& elem) {
            return elem == 6;
        });
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
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