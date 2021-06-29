//
// Created by Darwin Yuan on 2021/6/21.
//

#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

SCENARIO("ObjectArray") {
    ObjectArray<int, 10> array;

    static_assert(std::is_trivially_destructible_v<ObjectArray<int, 10>>);

    REQUIRE(array.GetNum() == 0);
    REQUIRE(array.None());
    array.Append(1);

    WHEN("Erase")
    {
        REQUIRE(array.GetNum() == 1);
        REQUIRE(!array.None());
        array.Erase(0);
        REQUIRE(array.GetNum() == 0);
        REQUIRE(array.None());
    }

    WHEN("Remove")
    {
        REQUIRE(array.GetNum() == 1);
        REQUIRE(!array.None());

        array.Remove(&array[0]);

        REQUIRE(array.GetNum() == 0);
        REQUIRE(array.None());
    }

    WHEN("copy") {
        auto array2 = std::move(array);
        REQUIRE(array2.GetNum() == 1);
        REQUIRE(array.GetNum() == 0);
    }
}

namespace {
    int object_count = 0;

    struct Foo {
        int a;
        Foo(int a) : a{a} { object_count++; }
        ~Foo() { object_count--; }
    };

    static_assert(!std::is_trivially_destructible_v<ObjectArray<Foo, 10>>);
}

SCENARIO("ObjectArray Cleanup") {
    {
        ObjectArray<Foo, 10> array;
        REQUIRE(object_count == 0);
        array.Append(1);
        REQUIRE(object_count == 1);
        array.Append(2);
        REQUIRE(object_count == 2);
    }
    REQUIRE(object_count == 0);
}

SCENARIO("ObjectArray equality") {
    ObjectArray<int, 10> array1;
    array1.Append(0);
    array1.Append(1);

    {
        ObjectArray<int, 10> array2;
        array2.Append(1);
        array2.Append(0);
        //REQUIRE(array1 == array2);
        array2.Append(0);
        //REQUIRE(array1 != array2);
    }

    {
        ObjectArray<int, 10> array2;
        array2.Append(1);
        array2.Append(2);
        //REQUIRE(array1 != array2);
    }
}

SCENARIO("ObjectArray iterator") {
    ObjectArray<int, 10> array;
    array.Append(2);
    array.Append(3);
    array.Append(4);
    array.Append(1);
    array.Append(8);
    array.Append(7);

    auto n = 0;
    auto sum = 0;
    for(auto&& i : array) {
        i += 1;
        n++;
        sum += i;
    }

    REQUIRE(n == 6);
    REQUIRE(sum == 2 + 4 + 3 + 1 + 8 + 7 + 6);
}

SCENARIO("ObjectArray const iterator") {
    ObjectArray<int, 10> array{2,3,4,1,8,7};

    {
        ObjectArray<int, 10> const& constArray = array;
        auto n = 0;
        auto sum = 0;
        for(auto&& i : constArray) {
            n++;
            sum += i;
        }

        REQUIRE(n == 6);
        REQUIRE(sum == 2 + 4 + 3 + 1 + 8 + 7);
    }

    WHEN("iterate with non-const view")
    {
        auto n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : array.WithIndex()) {
            REQUIRE(i == n);
            n++;
            elem += 1;
            sum += elem;
        }
        REQUIRE(n == 6);
        REQUIRE(sum == 2 + 4 + 3 + 1 + 8 + 7 + 6);
    }

    WHEN("iterate with const view")
    {
        ObjectArray<int, 10> const& constArray = array;
        auto n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : constArray.WithIndex()) {
            REQUIRE(i == n);
            n++;
            sum += elem;
        }
        REQUIRE(n == 6);
        REQUIRE(sum == 2 + 4 + 3 + 1 + 8 + 7);
    }

    WHEN("iterate with const view from")
    {
        ObjectArray<int, 10> const& constArray = array;
        auto n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : constArray.From(1).WithIndex()) {
            n++;
            REQUIRE(i == n);
            sum += elem;
        }
        REQUIRE(n == 5);
        REQUIRE(sum == 4 + 3 + 1 + 8 + 7);
    }

    WHEN("iterate with const view Begin -> WithIndex")
    {
        ObjectArray<int, 10> const& constArray = array;
        auto n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : constArray.From(1).WithIndex()) {
            n++;
            REQUIRE(i == n);
            sum += elem;
        }
        REQUIRE(n == 5);
        REQUIRE(sum == 4 + 3 + 1 + 8 + 7);
    }

    WHEN("iterate with const view Begin without Index")
    {
        ObjectArray<int, 10> const& constArray = array;
        auto n = 0;
        auto sum = 0;
        for(auto&& elem : constArray.From(1)) {
            n++;
            sum += elem;
        }
        REQUIRE(n == 5);
        REQUIRE(sum == 4 + 3 + 1 + 8 + 7);
    }

    WHEN("iterate with non-const view from")
    {
        auto n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : array.From(1).WithIndex()) {
            n++;
            REQUIRE(i == n);
            elem += 1;
            sum += elem;
        }
        REQUIRE(n == 5);
        REQUIRE(sum == 4 + 3 + 1 + 8 + 7 + 5);
    }
}

SCENARIO("ObjectArray Slice Sort") {
    ObjectArray<int, 10> array{2,3,4,1,8,7};

    array.Slice(1, -2).Sort();

    REQUIRE(array[0] == 2);
    REQUIRE(array[1] == 1);
    REQUIRE(array[2] == 3);
    REQUIRE(array[3] == 4);
    REQUIRE(array[4] == 8);
    REQUIRE(array[5] == 7);
}

SCENARIO("ObjectArray Scope Sort") {
    ObjectArray<int, 10> array{2,3,4,1,8,7};

    array.Scope(0x0c).Sort();

    REQUIRE(array[0] == 2);
    REQUIRE(array[1] == 3);
    REQUIRE(array[2] == 1);
    REQUIRE(array[3] == 4);
    REQUIRE(array[4] == 8);
    REQUIRE(array[5] == 7);
}

SCENARIO("ObjectArray Slice/Scope Sort") {
    ObjectArray<int, 10> array{2,3,4,1,8,7};

    array.Slice(1, -2).Scope(0x2d).Sort();

    REQUIRE(array[0] == 2);
    REQUIRE(array[1] == 3);
    REQUIRE(array[2] == 1);
    REQUIRE(array[3] == 4);
    REQUIRE(array[4] == 8);
    REQUIRE(array[5] == 7);
}

namespace {
    struct Bar {
        int a;
        int b;
    };

    static_assert(std::is_trivially_destructible_v<Bar>);
    static_assert(std::is_trivially_destructible_v<ObjectArray<Bar, 10>>);

    static_assert(std::is_copy_constructible_v<Bar>);
    static_assert(std::is_copy_constructible_v<ObjectArray<Bar, 10>>);

    static_assert(std::is_move_constructible_v<Bar>);
    static_assert(std::is_move_constructible_v<ObjectArray<Bar, 10>>);

    static_assert(std::is_copy_assignable_v<Bar>);
    static_assert(std::is_copy_assignable_v<ObjectArray<Bar, 10>>);

    static_assert(std::is_move_assignable_v<Bar>);
    static_assert(std::is_move_assignable_v<ObjectArray<Bar, 10>>);
}

SCENARIO("ObjectArray with struct") {
    ObjectArray<Bar, 10> array = {{10, 20}, {30, 40}, {40, 50}, {50, 60}};

    auto sum_a = 0;
    auto sum_b = 0;

    for(auto&& [elem, i] : array.WithIndex()) {
        sum_a += elem.a;
        sum_b += elem.b;
    }

    REQUIRE(sum_a == 130);
    REQUIRE(sum_b == 170);
};

SCENARIO("ObjectArray Foreach") {
    ObjectArray<int, 10> array1{0, 1, 2};

    {
        auto times = 0;
        bool result = array1.ForEach([&times](auto &&r) {
            times++;
            return r != 0;
        });
        REQUIRE(!result);
        REQUIRE(times == 1);
    }

    {
        auto times = 0;
        bool result = array1.ForEach([&times](auto &&r) {
            times++;
            return r == 0;
        });
        REQUIRE(!result);
        REQUIRE(times == 2);
    }

    {
        auto times = 0;
        bool result = array1.ForEach([&times](auto &&r) {
            times++;
            return true;
        });
        REQUIRE(result);
        REQUIRE(times == 3);
    }

    {
        auto times = 0;
        auto result = array1.ForEach([&times](auto &&r) {
            times++;
            return 1;
        });
        REQUIRE(result == 1);
        REQUIRE(times == 1);
    }

    {
        auto times = 0;
        ObjectArray<int, 10>::BitMap scope{0x01};
        auto result = array1.ForEach(scope, [&times](auto &&r) {
            r = 10;
            times++;
            return 1;
        });
        REQUIRE(result == 1);
        REQUIRE(times == 1);
        REQUIRE(array1[0] == 10);
    }

    {
        auto times = 0;
        auto result = array1.ForEach([&times](auto &&r) {
            times++;
            return 0;
        });
        REQUIRE(result == 0);
        REQUIRE(times == 3);
    }

    {
        auto times = 0;
        array1.ForEach([&times](auto &&r) {
            times++;
        });
        REQUIRE(times == 3);
    }

    {
        ObjectArray<int, 10> a = {1,2,3};
        REQUIRE(a.GetNum() == 3);
        REQUIRE(a[0] == 1);
        REQUIRE(a[1] == 2);
        REQUIRE(a[2] == 3);
    }

    {
        ObjectArray<int, 10> a = {1,2,3};

        int n = 0;
        auto sum = 0;
        for(auto&& elem : a.Scope(0x02)) {
            n++;
            sum += elem;
        }

        REQUIRE(n == 1);
        REQUIRE(sum == 2);
    }

    {
        ObjectArray<int, 10> a = {1,2,3};

        int n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : a.Scope(0x02).WithIndex()) {
            REQUIRE(i == 1);
            n++;
            sum += elem;
        }

        REQUIRE(n == 1);
        REQUIRE(sum == 2);
    }

    {
        ObjectArray<int, 10> a = {1,2,3};
        ObjectArray<int, 10>::BitMap scope{0x02};

        int n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : a.Slice(1, -1).Scope(scope).WithIndex()) {
            ++n;
            REQUIRE(i == 1);
            sum += elem;
        }

        REQUIRE(n == 1);
        REQUIRE(sum == 2);
    }

    {
        ObjectArray<int, 10> a = {1,2,3};
        ObjectArray<int, 10>::BitMap scope{0x2};

        int n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : a.From(1).Scope(scope).WithIndex()) {
            REQUIRE(i == 1);
            n++;
            sum += elem;
        }

        REQUIRE(n == 1);
        REQUIRE(sum == 2);
    }

    {
        ObjectArray<int, 10> a = {1,2,3};

        int n = 0;
        auto sum = 0;
        for(auto&& [elem, i] : a.Until(-1).WithIndex()) {
            REQUIRE(i == n);
            n++;
            sum += elem;
        }

        REQUIRE(n == 2);
        REQUIRE(sum == 1 + 2);
    }

    {
        ObjectArray<int, 10> a = {3,2,1};

        a.Sort();
    }
}

namespace {
    struct Thing {
        Thing() : a{0} {}
        Thing(int a) : a{a} {}
        Thing(Thing&& rhs) : a{rhs.a} {
            rhs.a = 10;
        }
        ~Thing() { a = 15; }

        auto operator==(Thing const& rhs) const -> bool {
            return a == rhs.a;
        }
        int a;
    };

    using ThingArray = ObjectArray<Thing, 5>;

    static_assert(!std::is_trivially_constructible_v<Thing>);
    static_assert(!std::is_trivially_constructible_v<ThingArray>);

    static_assert(!std::is_trivially_destructible_v<Thing>);
    static_assert(!std::is_trivially_destructible_v<ThingArray>);

    static_assert(!std::is_copy_constructible_v<Thing>);
    static_assert(!std::is_copy_constructible_v<ThingArray>);

    static_assert(std::is_move_constructible_v<Thing>);
    static_assert(std::is_move_constructible_v<ThingArray>);

    static_assert(!std::is_copy_assignable_v<Thing>);
    static_assert(!std::is_copy_assignable_v<ThingArray>);

    // this is fine for array.
    static_assert(!std::is_move_assignable_v<Thing>);
    static_assert(std::is_move_assignable_v<ThingArray>);
}

SCENARIO("init with init list") {
    ThingArray array;
    array.Append(1);

    Thing thing{2};

    // copy cons is not allowed
    // array.Append(thing);
    array.Append(std::move(thing));
    REQUIRE(array.GetNum() == 2);
    REQUIRE(thing.a == 10);
    REQUIRE(array[1].a == 2);

    WHEN("Access By At") {
        REQUIRE(array.At(0)->a == 1);
        REQUIRE(array.At(1)->a == 2);
        REQUIRE(array.At(2) == nullptr);
    }

    WHEN("Erase 1st one") {
        array.Erase(0);
        REQUIRE(array.GetNum() == 1);
        REQUIRE(array[1].a == 15);
        REQUIRE(array[0].a == 2);
    }

    WHEN("Erase 2nd one") {
        array.Erase(1);
        REQUIRE(array.GetNum() == 1);
        REQUIRE(array[1].a == 15);
        REQUIRE(array[0].a == 1);
    }

    WHEN("Replace") {
        array.Replace(0, Thing{3});
        REQUIRE(array.GetNum() == 2);
        REQUIRE(array[0].a == 3);
    }

    WHEN("Remove") {
        array.Remove(&array[0]);
        REQUIRE(array.GetNum() == 1);
        REQUIRE(array[0].a == 2);
    }

    WHEN("ReplaceObj") {
        array.ReplaceObj(array[0], 7);
        REQUIRE(array.GetNum() == 2);
        REQUIRE(array[0].a == 7);
    }

    WHEN("RemoveBy") {
        array.RemoveBy([](auto&& elem) {
            return elem.a == 1;
        });

        REQUIRE(array.GetNum() == 1);
        REQUIRE(array[0].a == 2);
    }

    WHEN("Added moe elems") {
        array.Append(3);
        array.Append(4);
        array.Append(5);
        REQUIRE(array.GetNum() == 5);
        REQUIRE(array.All());

        WHEN("CleanUpBy") {
            array.CleanUpBy([](auto&& elem) {
                return elem.a <= 3;
            });

            REQUIRE(array.GetNum() == 2);
            REQUIRE(array.Exists(Thing{4}));
            REQUIRE(array.Exists(Thing{5}));
        }

        WHEN("Clear") {
            array.Clear();
            REQUIRE(array.GetNum() == 0);
            REQUIRE(array.None());
            REQUIRE_FALSE(array.Any());
        }

        WHEN("ClearFrom") {
            array.ClearFrom(2);
            REQUIRE(array.GetNum() == 2);
            REQUIRE(array[0].a == 1);
            REQUIRE(array[1].a == 2);
        }

        WHEN("ClearUntil") {
            REQUIRE(array.GetNum() == 5);
            array.ClearUntil(3);
            REQUIRE(array.GetNum() == 2);
            REQUIRE(array[0].a == 4);
            REQUIRE(array[1].a == 5);
        }

        WHEN("ClearRange") {
            REQUIRE(array.GetNum() == 5);
            array.Clear(1, -1);
            REQUIRE(array.GetNum() == 2);
            REQUIRE(array[0].a == 1);
            REQUIRE(array[1].a == 5);
        }

        WHEN("CleanUp") {
            array.CleanUp(0x0a); // 01010
            REQUIRE(array.GetNum() == 3);
            REQUIRE(array[0].a == 1);
            REQUIRE(array[1].a == 5);
            REQUIRE(array[2].a == 3);
        }

        WHEN("CleanUpEx") {
            array.CleanUpEx(0x0a); // 00101
            REQUIRE(array.GetNum() == 2);
            REQUIRE(array[0].a == 4);
            REQUIRE(array[1].a == 2);
        }
    }

    WHEN("Compare Equality") {
        ThingArray array2;
        array2.Append(2);
        array2.Append(1);
        REQUIRE(array == array2);
        array2.Append(2);
        REQUIRE(array != array2);
    }

    WHEN("Compare Equality with same num") {
        ThingArray array2;
        array2.Append(3);
        array2.Append(1);
        REQUIRE(array != array2);
    }
}

SCENARIO("ObjectArray PartialSort") {
    ObjectArray<int, 10> a = {4,3,1,2};

    auto n = 0;
    auto sum = 0;
    for(auto&& elem : a.PartialSort(2)) {
        n++;
        sum += elem;
    }

    REQUIRE(n == 2);
    REQUIRE(sum == 3);
}

SCENARIO("ObjectArray Slice PartialSort") {
    ObjectArray<int, 10> a = {4,3,1,2};

    auto n = 0;
    auto sum = 0;
    for(auto&& elem : a.Slice(1, -1).PartialSort(2)) {
        n++;
        sum += elem;
    }

    REQUIRE(n == 2);
    REQUIRE(sum == 4);

    REQUIRE(a[0] == 4);
    REQUIRE(a[1] == 1);
    REQUIRE(a[2] == 3);
}

SCENARIO("ObjectArray Slice Scope PartialSort") {
    ObjectArray<int, 10> a = {4,3,1,2};

    auto n = 0;
    auto sum = 0;
    for(auto&& elem : a.Slice(1, -1).Scope(0xFF).PartialSort(2)) {
        n++;
        sum += elem;
    }

    REQUIRE(n == 2);
    REQUIRE(sum == 4);

    REQUIRE(a[0] == 4);
    REQUIRE(a[1] == 1);
    REQUIRE(a[2] == 3);

    a[0] = 5;
    REQUIRE(a[0] == 5);
}

namespace {
    struct TT {
        ~TT() { a=0; }
        int a;
    };
}

SCENARIO("Array of const object") {
    ObjectArray<int const, 10> array{30, 10, 20};

//    array.Append(10);
//    array.Append(20);

//    REQUIRE(array.GetNum() == 2);
//    array.Replace(0, 30);
//    REQUIRE(array[0] == 30);
}