//
// Created by Darwin Yuan on 2021/6/25.
//

#include <cub/base/Placement.h>
#include <catch.hpp>

namespace {
    constexpr short DE_MAGIC = 0xE7A2;
    constexpr short CO_MAGIC = 0xABCD;
    static bool cons = false;

    struct Foo {
        Foo() = default;
        Foo(long long a) : a(a), b{CO_MAGIC} {
            cons = true;
        }

        Foo(Foo&& rhs) : a(rhs.a), b{rhs.b} {}

        long long a;
        short b;

        ~Foo() {
            b = DE_MAGIC;
            cons = false;
        }
    };

    static_assert(!std::is_trivial_v<Foo>);
    static_assert(!std::is_trivial_v<Placement<Foo>>);

    static_assert(std::is_constructible_v<Foo>);
    static_assert(std::is_constructible_v<Placement<Foo>>);

    static_assert(std::is_default_constructible_v<Foo>);
    static_assert(std::is_default_constructible_v<Placement<Foo>>);

    static_assert(!std::is_trivially_destructible_v<Foo>);
    static_assert(!std::is_trivially_destructible_v<Placement<Foo>>);

    static_assert(!std::is_trivially_default_constructible_v<Foo>);
    static_assert(!std::is_trivially_default_constructible_v<Placement<Foo>>);

    static_assert(!std::is_trivially_constructible_v<Foo>);
    static_assert(!std::is_trivially_constructible_v<Placement<Foo>>);

    static_assert(!std::is_trivially_copyable_v<Foo>);
    static_assert(!std::is_trivially_copyable_v<Placement<Foo>>);

    static_assert(!std::is_trivially_copy_constructible_v<Foo>);
    static_assert(!std::is_trivially_copy_constructible_v<Placement<Foo>>);

    static_assert(!std::is_trivially_move_constructible_v<Foo>);
    static_assert(!std::is_trivially_move_constructible_v<Placement<Foo>>);

    static_assert(!std::is_trivially_copy_assignable_v<Foo>);
    static_assert(!std::is_trivially_copy_assignable_v<Placement<Foo>>);

    static_assert(!std::is_trivially_move_assignable_v<Foo>);
    static_assert(!std::is_trivially_move_assignable_v<Placement<Foo>>);

    struct Bar {
        int a;
    };

    static_assert(std::is_trivial_v<Bar>);
    static_assert(std::is_trivial_v<Placement<Bar>>);

    static_assert(std::is_trivially_destructible_v<Bar>);
    static_assert(std::is_trivially_destructible_v<Placement<Bar>>);

    static_assert(std::is_trivially_constructible_v<Bar>);
    static_assert(std::is_trivially_constructible_v<Placement<Bar>>);

    static_assert(std::is_trivially_copyable_v<Bar>);
    static_assert(std::is_trivially_copyable_v<Placement<Bar>>);

    static_assert(std::is_trivially_copy_constructible_v<Bar>);
    static_assert(std::is_trivially_copy_constructible_v<Placement<Bar>>);

    static_assert(std::is_trivially_move_constructible_v<Bar>);
    static_assert(std::is_trivially_move_constructible_v<Placement<Bar>>);

    static_assert(std::is_trivially_copy_assignable_v<Bar>);
    static_assert(std::is_trivially_copy_assignable_v<Placement<Bar>>);

    static_assert(std::is_trivially_move_assignable_v<Bar>);
    static_assert(std::is_trivially_move_assignable_v<Placement<Bar>>);

    static_assert(std::is_trivially_default_constructible_v<Bar>);
    static_assert(std::is_trivially_default_constructible_v<Placement<Bar>>);

    struct Thing {
        int a;
        int b;
        ~Thing() {}
    };

    static_assert(std::is_constructible_v<Thing>);
    static_assert(std::is_constructible_v<Placement<Thing>>);

    static_assert(std::is_default_constructible_v<Thing>);
    static_assert(std::is_default_constructible_v<Placement<Thing>>);

    static_assert(!std::is_trivial_v<Thing>);
    static_assert(!std::is_trivial_v<Placement<Thing>>);

    static_assert(!std::is_trivially_destructible_v<Thing>);
    static_assert(!std::is_trivially_destructible_v<Placement<Thing>>);

    static_assert(!std::is_trivially_default_constructible_v<Thing>);
    static_assert(!std::is_trivially_default_constructible_v<Placement<Thing>>);

    static_assert(!std::is_trivially_constructible_v<Thing>);
    static_assert(!std::is_trivially_constructible_v<Placement<Thing>>);

    static_assert(!std::is_trivially_copyable_v<Thing>);
    static_assert(!std::is_trivially_copyable_v<Placement<Thing>>);

    static_assert(!std::is_trivially_copy_constructible_v<Thing>);
    static_assert(!std::is_trivially_copy_constructible_v<Placement<Thing>>);

    static_assert(!std::is_trivially_move_constructible_v<Thing>);
    static_assert(!std::is_trivially_move_constructible_v<Placement<Thing>>);

    static_assert(std::is_trivially_copy_assignable_v<Thing>);
    static_assert(std::is_trivially_copy_assignable_v<Placement<Thing>>);

    static_assert(std::is_trivially_move_assignable_v<Thing>);
    static_assert(std::is_trivially_move_assignable_v<Placement<Thing>>);

    struct Thing1 {
        Thing thing;
    };

    static_assert(std::is_constructible_v<Thing1>);
    static_assert(std::is_constructible_v<Placement<Thing1>>);

    static_assert(std::is_default_constructible_v<Thing1>);
    static_assert(std::is_default_constructible_v<Placement<Thing1>>);

    static_assert(!std::is_trivial_v<Thing1>);
    static_assert(!std::is_trivial_v<Placement<Thing1>>);

    static_assert(!std::is_trivially_destructible_v<Thing1>);
    static_assert(!std::is_trivially_destructible_v<Placement<Thing1>>);

    static_assert(!std::is_trivially_default_constructible_v<Thing1>);
    static_assert(!std::is_trivially_default_constructible_v<Placement<Thing1>>);

    static_assert(!std::is_trivially_constructible_v<Thing1>);
    static_assert(!std::is_trivially_constructible_v<Placement<Thing1>>);

    static_assert(!std::is_trivially_copyable_v<Thing1>);
    static_assert(!std::is_trivially_copyable_v<Placement<Thing1>>);

    static_assert(!std::is_trivially_copy_constructible_v<Thing1>);
    static_assert(!std::is_trivially_copy_constructible_v<Placement<Thing1>>);

    static_assert(!std::is_trivially_move_constructible_v<Thing1>);
    static_assert(!std::is_trivially_move_constructible_v<Placement<Thing1>>);

    static_assert(std::is_trivially_copy_assignable_v<Thing1>);
    static_assert(std::is_trivially_copy_assignable_v<Placement<Thing1>>);

    static_assert(std::is_trivially_move_assignable_v<Thing1>);
    static_assert(std::is_trivially_move_assignable_v<Placement<Thing1>>);

    struct Thing2 {
        Thing2() = default;
        Thing2(int a, int b) : a{a}, b{b} {}

        int a;
        int b;
    };

    static_assert(std::is_constructible_v<Thing2>);
    static_assert(std::is_constructible_v<Placement<Thing2>>);

    static_assert(std::is_default_constructible_v<Thing2>);
    static_assert(std::is_default_constructible_v<Placement<Thing2>>);

    static_assert(std::is_trivial_v<Thing2>);
    static_assert(std::is_trivial_v<Placement<Thing2>>);

    static_assert(std::is_trivially_destructible_v<Thing2>);
    static_assert(std::is_trivially_destructible_v<Placement<Thing2>>);

    static_assert(std::is_trivially_default_constructible_v<Thing2>);
    static_assert(std::is_trivially_default_constructible_v<Placement<Thing2>>);

    static_assert(std::is_trivially_constructible_v<Thing2>);
    static_assert(std::is_trivially_constructible_v<Placement<Thing2>>);

    static_assert(std::is_trivially_copyable_v<Thing2>);
    static_assert(std::is_trivially_copyable_v<Placement<Thing2>>);

    static_assert(std::is_trivially_copy_constructible_v<Thing2>);
    static_assert(std::is_trivially_copy_constructible_v<Placement<Thing2>>);

    static_assert(std::is_trivially_move_constructible_v<Thing2>);
    static_assert(std::is_trivially_move_constructible_v<Placement<Thing2>>);

    static_assert(std::is_trivially_copy_assignable_v<Thing2>);
    static_assert(std::is_trivially_copy_assignable_v<Placement<Thing2>>);

    static_assert(std::is_trivially_move_assignable_v<Thing2>);
    static_assert(std::is_trivially_move_assignable_v<Placement<Thing2>>);

    struct Thing3 {
        Thing3() = default;
        Thing3(int a, int b) : a{a}, b{b} {}

        int a{};
        int b;
    };

    static_assert(std::is_constructible_v<Thing3>);
    static_assert(std::is_constructible_v<Placement<Thing3>>);

    static_assert(std::is_default_constructible_v<Thing3>);
    static_assert(std::is_default_constructible_v<Placement<Thing3>>);

    static_assert(!std::is_trivial_v<Thing3>);
    static_assert(!std::is_trivial_v<Placement<Thing3>>);

    static_assert(std::is_trivially_destructible_v<Thing3>);
    static_assert(std::is_trivially_destructible_v<Placement<Thing3>>);

    static_assert(!std::is_trivially_default_constructible_v<Thing3>);
    static_assert(!std::is_trivially_default_constructible_v<Placement<Thing3>>);

    static_assert(!std::is_trivially_constructible_v<Thing3>);
    static_assert(!std::is_trivially_constructible_v<Placement<Thing3>>);

    static_assert(std::is_trivially_copyable_v<Thing3>);
    static_assert(std::is_trivially_copyable_v<Placement<Thing3>>);

    static_assert(std::is_trivially_copy_constructible_v<Thing3>);
    static_assert(std::is_trivially_copy_constructible_v<Placement<Thing3>>);

    static_assert(std::is_trivially_move_constructible_v<Thing3>);
    static_assert(std::is_trivially_move_constructible_v<Placement<Thing3>>);

    static_assert(std::is_trivially_copy_assignable_v<Thing3>);
    static_assert(std::is_trivially_copy_assignable_v<Placement<Thing3>>);

    static_assert(std::is_trivially_move_assignable_v<Thing3>);
    static_assert(std::is_trivially_move_assignable_v<Placement<Thing3>>);

    struct Thing4 {
        Thing4() = default;
        Thing4(Thing4 const& rhs) : a{rhs.a}, b{rhs.b} {}

        int a;
        int b;
    };

    static_assert(std::is_constructible_v<Thing4>);
    static_assert(std::is_constructible_v<Placement<Thing4>>);

    static_assert(std::is_default_constructible_v<Thing4>);
    static_assert(std::is_default_constructible_v<Placement<Thing4>>);

    static_assert(!std::is_trivial_v<Thing4>);
    static_assert(!std::is_trivial_v<Placement<Thing4>>);

    static_assert(std::is_trivially_destructible_v<Thing4>);
    static_assert(std::is_trivially_destructible_v<Placement<Thing4>>);

    static_assert(std::is_trivially_constructible_v<Thing4>);
    static_assert(std::is_trivially_constructible_v<Placement<Thing4>>);

    static_assert(std::is_trivially_default_constructible_v<Thing4>);
    static_assert(std::is_trivially_default_constructible_v<Placement<Thing4>>);

    static_assert(!std::is_trivially_copyable_v<Thing4>);
    static_assert(!std::is_trivially_copyable_v<Placement<Thing4>>);

    static_assert(!std::is_trivially_copy_constructible_v<Thing4>);
    static_assert(!std::is_trivially_copy_constructible_v<Placement<Thing4>>);

    static_assert(!std::is_trivially_move_constructible_v<Thing4>);
    static_assert(!std::is_trivially_move_constructible_v<Placement<Thing4>>);

    static_assert(std::is_trivially_copy_assignable_v<Thing4>);
    static_assert(std::is_trivially_copy_assignable_v<Placement<Thing4>>);

    static_assert(std::is_trivially_move_assignable_v<Thing4>);
    static_assert(std::is_trivially_move_assignable_v<Placement<Thing4>>);

    struct Thing5 {
        int a;
        int& b;
    };

    static_assert(!std::is_constructible_v<Thing5>);
    static_assert(std::is_constructible_v<Placement<Thing5>>);

    static_assert(!std::is_default_constructible_v<Thing5>);
    static_assert(std::is_default_constructible_v<Placement<Thing5>>);

    static_assert(std::is_trivial_v<Thing5>);
    static_assert(!std::is_trivial_v<Placement<Thing5>>);

    static_assert(std::is_trivially_destructible_v<Thing5>);
    static_assert(std::is_trivially_destructible_v<Placement<Thing5>>);

    static_assert(!std::is_trivially_constructible_v<Thing5>);
    static_assert(!std::is_trivially_constructible_v<Placement<Thing5>>);

    static_assert(!std::is_trivially_default_constructible_v<Thing5>);
    static_assert(!std::is_trivially_default_constructible_v<Placement<Thing5>>);

    static_assert(std::is_trivially_copyable_v<Thing5>);
    static_assert(std::is_trivially_copyable_v<Placement<Thing5>>);

    static_assert(std::is_trivially_copy_constructible_v<Thing5>);
    static_assert(std::is_trivially_copy_constructible_v<Placement<Thing5>>);

    static_assert(std::is_trivially_move_constructible_v<Thing5>);
    static_assert(std::is_trivially_move_constructible_v<Placement<Thing5>>);

    static_assert(!std::is_trivially_copy_assignable_v<Thing5>);
    static_assert(!std::is_trivially_copy_assignable_v<Placement<Thing5>>);

    static_assert(!std::is_trivially_move_assignable_v<Thing5>);
    static_assert(!std::is_trivially_move_assignable_v<Placement<Thing5>>);
}

SCENARIO("Placement") {
    Placement<Foo> obj;

    static_assert(alignof(Placement<Foo>) == alignof(Foo));

    REQUIRE(!cons);

    obj.Emplace(100);

    REQUIRE(cons);
    REQUIRE(obj->a == 100);
    REQUIRE((*obj).a == 100);
    REQUIRE(obj->b == CO_MAGIC);

    obj.Destroy();

    REQUIRE(!cons);
    REQUIRE(obj->b == DE_MAGIC);
}

SCENARIO("Reference Placement") {
    Placement<Thing5> c;

    int a = 1;
    int b = 2;
    c.Emplace(a, b);

    REQUIRE(c->a == a);
    REQUIRE(c->b == b);
}