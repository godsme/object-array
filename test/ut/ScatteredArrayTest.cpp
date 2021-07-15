//
// Created by Darwin Yuan on 2021/7/12.
//

#include <l0-infra/array/ScatteredArray.h>
#include <catch.hpp>

SCENARIO("Default ScatteredArray Initialization of trivial type should not be 0-initialized") {
    Placement<ScatteredArray<int, 10>> array;
    ::memset(&array, 0xFF, sizeof(array));
    array.Emplace();

    REQUIRE((*array)[0] != 0);
}

SCENARIO("ScatteredArray Test") {
    ScatteredArray<int, 10> foo {2, 6, 3};

    WHEN("Replace Object") {
        foo.ReplaceObj(foo[1], 10);
        REQUIRE(foo[1] == 10);
    }

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

    WHEN("find an existing object") {
        auto found = foo.FindIndex(6);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("find an existing object with index") {
        REQUIRE_FALSE(foo.FindIndex(7).has_value());
    }
}

SCENARIO("ScatteredArray Sort Test") {
    ScatteredArray<int, 10> foo {2, 6, 3};

    foo.Sort();

    REQUIRE(foo[0] == 2);
    REQUIRE(foo[1] == 3);
    REQUIRE(foo[2] == 6);

    foo.DescSort();

    REQUIRE(foo[0] == 6);
    REQUIRE(foo[1] == 3);
    REQUIRE(foo[2] == 2);
}

SCENARIO("ScatteredArray SortObject Test") {
    ScatteredArray<int, 10> foo {2, 6, 3};

    auto&& view = foo.SortView().Sort();

    REQUIRE(view[0] == 2);
    REQUIRE(view[1] == 3);
    REQUIRE(view[2] == 6);

    REQUIRE(foo[0] == 2);
    REQUIRE(foo[1] == 6);
    REQUIRE(foo[2] == 3);

    REQUIRE(!foo.All());
}

namespace {
    using IntArray = ScatteredArray<int, 10>;
    static_assert(std::is_move_constructible_v<IntArray>);
    static_assert(std::is_copy_constructible_v<IntArray>);
    static_assert(std::is_move_assignable_v<IntArray>);
    static_assert(std::is_copy_assignable_v<IntArray>);
    static_assert(!std::is_trivially_constructible_v<IntArray>);
    static_assert(std::is_trivially_destructible_v<IntArray>);

    struct Foo {
        Foo() : a{0} {}
        Foo(int a) : a{a} {}
        ~Foo() { a = 0; }

        Foo(Foo const&) = default;

        auto operator=(Foo const&) -> Foo& = default;

        auto operator==(Foo const& rhs) const -> bool { return a == rhs.a; }
        auto operator!=(Foo const& rhs) const -> bool { return a != rhs.a; }

        int a;
    };

    using FooArray = ScatteredArray<Foo, 4>;

    static_assert(std::is_move_constructible_v<FooArray>);
    static_assert(std::is_copy_constructible_v<FooArray>);
    static_assert(std::is_move_assignable_v<FooArray>);
    static_assert(std::is_copy_assignable_v<FooArray>);
    static_assert(!std::is_trivially_constructible_v<FooArray>);
    static_assert(!std::is_trivially_destructible_v<FooArray>);

    struct Bar {
        Bar(int a) : a{a} {}
        int a;
    };

    using BarArray = ScatteredArray<Bar, 10>;

    static_assert(std::is_move_constructible_v<BarArray>);
    static_assert(std::is_copy_constructible_v<BarArray>);
    static_assert(std::is_move_assignable_v<BarArray>);
    static_assert(std::is_copy_assignable_v<BarArray>);
    static_assert(!std::is_trivially_constructible_v<BarArray>);
    static_assert(std::is_trivially_destructible_v<BarArray>);
}

SCENARIO("ScatteredObjectArray") {
    FooArray array{{1}, {2}, {3}};

    REQUIRE(array.GetNum() == 3);
    REQUIRE(array[0].a == 1);
    REQUIRE(array[1].a == 2);
    REQUIRE(array[2].a == 3);

    REQUIRE(array.IsPresent(0));
    REQUIRE(array.IsPresent(1));
    REQUIRE(array.IsPresent(2));
    REQUIRE(!array.IsPresent(3));

    WHEN("Clear") {
        array.Clear();
        REQUIRE(array.GetNum() == 0);
        REQUIRE(array[0].a == 0);
        REQUIRE(array[1].a == 0);
        REQUIRE(array[2].a == 0);
    }

    WHEN("Compare Equality") {
        REQUIRE((array != FooArray{{1}, {2}}));
        REQUIRE((array != FooArray{{1}}));
        REQUIRE((array != FooArray{{1}, {2}, {4}}));
        REQUIRE((array != FooArray{{1}, {2}, {3}, {4}}));

        REQUIRE((array == FooArray{{2}, {1}, {3}}));
        REQUIRE((array == FooArray{{2}, {3}, {1}}));
        REQUIRE((array == FooArray{{1}, {3}, {2}}));
        REQUIRE((array == FooArray{{1}, {2}, {3}}));
        REQUIRE((array == FooArray{{3}, {1}, {2}}));
        REQUIRE((array == FooArray{{3}, {2}, {1}}));
    }

    WHEN("Copy Cons") {
        FooArray array1{array};

        REQUIRE(array1.GetNum() == 3);
        REQUIRE(array1[0].a == 1);
        REQUIRE(array1[1].a == 2);
        REQUIRE(array1[2].a == 3);

        REQUIRE(array1.IsPresent(0));
        REQUIRE(array1.IsPresent(1));
        REQUIRE(array1.IsPresent(2));
        REQUIRE(!array.IsPresent(3));

        THEN("array should keep unchanged") {
            REQUIRE(array.GetNum() == 3);
            REQUIRE(array[0].a == 1);
            REQUIRE(array[1].a == 2);
            REQUIRE(array[2].a == 3);

            REQUIRE(array.IsPresent(0));
            REQUIRE(array.IsPresent(1));
            REQUIRE(array.IsPresent(2));
            REQUIRE(!array.IsPresent(3));
        }

        REQUIRE((array == array1));
    }

    WHEN("Move Cons") {
        FooArray array1{std::move(array)};

        REQUIRE(array1.GetNum() == 3);
        REQUIRE(array1[0].a == 1);
        REQUIRE(array1[1].a == 2);
        REQUIRE(array1[2].a == 3);

        REQUIRE(array1.IsPresent(0));
        REQUIRE(array1.IsPresent(1));
        REQUIRE(array1.IsPresent(2));
        REQUIRE(!array.IsPresent(3));

        THEN("array Has Been Cleared") {
            REQUIRE(array.GetNum() == 0);
            REQUIRE(array[0].a == 0);
            REQUIRE(array[1].a == 0);
            REQUIRE(array[2].a == 0);

            REQUIRE(!array.IsPresent(0));
            REQUIRE(!array.IsPresent(1));
            REQUIRE(!array.IsPresent(2));
            REQUIRE(!array.IsPresent(3));
        }

        REQUIRE((array != array1));
    }

    WHEN("Range For") {
        auto n = 0;
        auto sum = 0;

        for(auto&& elem : array) {
            n++;
            sum += elem.a;
        }

        REQUIRE(n == 3);
        REQUIRE(sum == 1 + 2 + 3);
    }

    WHEN("Range For on an empty array") {
        auto n = 0;
        auto sum = 0;

        for(auto&& elem : FooArray{}) {
            n++;
            sum += elem.a;
        }

        REQUIRE(n == 0);
        REQUIRE(sum == 0);
    }

    WHEN("ForEach") {
        auto n = 0;
        auto sum = 0;

        array.ForEach([&](auto&& elem) {
            n++;
            sum += elem.a;
        });

        REQUIRE(n == 3);
        REQUIRE(sum == 1 + 2 + 3);
    }

    WHEN("ForEach on an empty array") {
        auto n = 0;
        auto sum = 0;

        FooArray{}.ForEach([&](auto&& elem) {
            n++;
            sum += elem.a;
        });

        REQUIRE(n == 0);
        REQUIRE(sum == 0);
    }

    WHEN("ForEach With Index") {
        auto n = 0;
        auto sum = 0;

        for(auto&& [elem, i] : array.WithIndex()) {
            REQUIRE(n == i);
            n++;
            sum += elem.a;
        }

        REQUIRE(n == 3);
        REQUIRE(sum == 1 + 2 + 3);
    }

    WHEN("ForEach on an empty array With Index") {
        auto n = 0;
        auto sum = 0;
        FooArray array{};
        for(auto&& [elem, i] : array.WithIndex()) {
            REQUIRE(n == i);
            n++;
            sum += elem.a;
        }

        REQUIRE(n == 0);
        REQUIRE(sum == 0);
    }

    WHEN("Erase 1") {
        array.Erase(1);
        REQUIRE(array.GetNum() == 2);
        REQUIRE_FALSE(array.IsPresent(1));

        WHEN("Range For") {
            auto n = 0;
            auto sum = 0;

            auto sumIndex = 0;
            for(auto&& [elem, i] : array.WithIndex()) {
                sumIndex += i;
                n++;
                sum += elem.a;
            }

            REQUIRE(n == 2);
            REQUIRE(sum == 1 + 3);
            REQUIRE(sumIndex == 0 + 2);
        }
    }

    WHEN("Remove 2nd") {
        array.Remove(&array[1]);

        REQUIRE(array.GetNum() == 2);
        REQUIRE_FALSE(array.IsPresent(1));

        WHEN("Range For") {
            auto n = 0;
            auto sum = 0;

            auto sumIndex = 0;
            for(auto&& [elem, i] : array.WithIndex()) {
                sumIndex += i;
                n++;
                sum += elem.a;
            }

            REQUIRE(n == 2);
            REQUIRE(sum == 1 + 3);
            REQUIRE(sumIndex == 0 + 2);
        }
    }

    WHEN("RemoveBy") {
        array.RemoveBy([](auto&& elem) {
            return elem.a == 2;
        });

        REQUIRE(array.GetNum() == 2);
        REQUIRE_FALSE(array.IsPresent(1));

        WHEN("Range For") {
            auto n = 0;
            auto sum = 0;

            auto sumIndex = 0;
            for(auto&& [elem, i] : array.WithIndex()) {
                sumIndex += i;
                n++;
                sum += elem.a;
            }

            REQUIRE(n == 2);
            REQUIRE(sum == 1 + 3);
            REQUIRE(sumIndex == 0 + 2);
        }
    }

    WHEN("CleanUpBy") {
        array.CleanUpBy([](auto&& elem) {
            return elem.a <= 2;
        });

        REQUIRE(array.GetNum() == 1);
        REQUIRE_FALSE(array.IsPresent(0));
        REQUIRE_FALSE(array.IsPresent(1));
        REQUIRE(array.IsPresent(2));
        REQUIRE(array.GetOccupied() == decltype(array)::BitMap{0x04});

        WHEN("Range For") {
            auto n = 0;
            auto sum = 0;

            auto sumIndex = 0;
            for(auto&& [elem, i] : array.WithIndex()) {
                sumIndex += i;
                n++;
                sum += elem.a;
            }

            REQUIRE(n == 1);
            REQUIRE(sum == 3);
            REQUIRE(sumIndex == 2);
        }
    }

    WHEN("Find Or Append (not found)") {
        REQUIRE(!array.IsPresent(3));
        auto* result = array.FindOrAppend([](auto&& elem) {
            return elem.a == 5;
        });
        REQUIRE(result != nullptr);
        REQUIRE(array.IsPresent(3));
        result->a = 5;
        REQUIRE(array[3].a == 5);
    }

    WHEN("Find Or Append (found)") {
        REQUIRE(!array.IsPresent(3));
        auto* result = array.FindOrAppend([](auto&& elem) {
            return elem.a == 2;
        });
        REQUIRE(result != nullptr);
        REQUIRE(!array.IsPresent(3));
        result->a = 5;
        REQUIRE(array[1].a == 5);
    }

    WHEN("MinElem") {
        auto* min= array.MinElem([](auto&& l, auto&& r) {
            return l.a < r.a;
        });

        REQUIRE(min->a == 1);
    }

    WHEN("MinElemIndex") {
        auto minIndex = array.MinElemIndex([](auto&& l, auto&& r) {
            return l.a < r.a;
        });

        REQUIRE(*minIndex == 0);
    }

    WHEN("MaxElem") {
        auto* max= array.MaxElem([](auto&& l, auto&& r) {
            return l.a < r.a;
        });

        REQUIRE(max->a == 3);
    }

    WHEN("MaxElemIndex") {
        auto maxIndex = array.MaxElemIndex([](auto&& l, auto&& r) {
            return l.a < r.a;
        });

        REQUIRE(*maxIndex == 2);
    }
}

namespace {
    struct Thing {
        Thing() = default;
        Thing(Thing&&) {}
    };

    using ThingArray = ScatteredArray<Thing, 10>;
    static_assert(!std::is_copy_constructible_v<Thing>);
    static_assert(!std::is_copy_constructible_v<ThingArray>);

    static_assert(!std::is_copy_assignable_v<Thing>);
    static_assert(!std::is_copy_assignable_v<ThingArray>);

    static_assert(std::is_move_constructible_v<Thing>);
    static_assert(std::is_move_constructible_v<ThingArray>);

    static_assert(!std::is_move_assignable_v<Thing>);
    static_assert(std::is_move_assignable_v<ThingArray>);

    static_assert(std::is_constructible_v<ThingArray>);
    static_assert(!std::is_trivially_constructible_v<ThingArray>);

}

SCENARIO("move cons Thing") {
    Thing a;
    Thing b{std::move(a)};
}

namespace {
    struct Thing2 {
        Thing2(Thing2 const&) {}
    };

    using Thing2Array = ScatteredArray<Thing2, 10>;
    static_assert(std::is_copy_constructible_v<Thing2>);
    static_assert(std::is_copy_constructible_v<Thing2Array>);

    static_assert(std::is_copy_assignable_v<Thing2>);
    static_assert(std::is_copy_assignable_v<Thing2Array>);

    static_assert(std::is_move_constructible_v<Thing2>);
    static_assert(std::is_move_constructible_v<Thing2Array>);

    static_assert(std::is_move_assignable_v<Thing2>);
    static_assert(std::is_move_assignable_v<Thing2Array>);

}

namespace {
    struct Thing3 {
        Thing3() = default;
        Thing3(Thing2 const&) {}
        Thing3(Thing2&&) = delete;
    };

    using Thing3Array = ScatteredArray<Thing3, 10>;
    static_assert(std::is_copy_constructible_v<Thing3>);
    static_assert(std::is_copy_constructible_v<Thing3Array>);

    static_assert(std::is_copy_assignable_v<Thing3>);
    static_assert(std::is_copy_assignable_v<Thing3Array>);

    static_assert(std::is_move_constructible_v<Thing3>);
    static_assert(std::is_move_constructible_v<Thing3Array>);

    static_assert(std::is_move_assignable_v<Thing3>);
    static_assert(std::is_move_assignable_v<Thing3Array>);
}

SCENARIO("move cons Thing3Array") {
    Thing3 a;
    Thing3 b{std::move(a)};

    Thing3Array aa;
    Thing3Array ba{std::move(aa)};

    aa.Append();
    aa.Append();

    REQUIRE(aa.GetNum() == 2);

    Thing3Array ca{std::move(aa)};

    REQUIRE(ca.GetNum() == 2);
    REQUIRE(aa.GetNum() == 0);
}