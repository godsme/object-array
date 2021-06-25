//
// Created by Darwin Yuan on 2021/6/22.
//

#include <object-array/ArrayView.h>
#include <catch.hpp>
#include <cub/base/StructWrapper.h>

namespace {
    struct Foo {
        int array[10];
        uint8_t num;
    };
}

SCENARIO("ArrayView Test") {
    Foo foo{{1,2,3,4,5,6,7,8}, 8};

    {
        ArrayView lvalueView{foo.array, foo.num};
        static_assert(sizeof(decltype(ArrayView{foo.array, foo.num}.Slice(1,2)))
                      > sizeof(decltype(lvalueView.Slice(1,2))));

        static_assert(sizeof(decltype(ArrayView{foo.array, foo.num}.Slice(1,2).Scope(0xFF)))
                      > sizeof(decltype(lvalueView.Slice(1,2).Scope(0xFF))));
    }


    WHEN("r-value find an existing elem") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,2).FindIndex(2);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("r-value find an existing elem with Scope") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,6).Scope(0xF0).FindIndex(5);
        REQUIRE(found.has_value());
        REQUIRE(*found == 4);
    }

    WHEN("r-value find a non-existing elem with Scope") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,6).Scope(0xF0).FindIndex(1);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("r-value find another non-existing elem with Scope") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,6).Scope(0xF0).FindIndex(8);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("l-value find a non-existing elem with Scope") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,6).Scope(0xF0).FindIndex(1);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("l-value find another non-existing elem with Scope") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,6).Scope(0xF0).FindIndex(8);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("r-value find a non-existing elem") {
        auto found = ArrayView{foo.array, foo.num}.Slice(1,2).FindIndex(4);
        REQUIRE_FALSE(found.has_value());
    }

    WHEN("l-value find an existing elem") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,2).FindIndex(2);
        REQUIRE(found.has_value());
        REQUIRE(*found == 1);
    }

    WHEN("l-value find a non-existing elem") {
        ArrayView view{foo.array, foo.num};
        auto found = view.Slice(1,2).FindIndex(4);
        REQUIRE_FALSE(found.has_value());
    }
}

namespace {
    struct Dummy {
        int a[10];
        uint8_t num;
    };
}

SCENARIO("ArrayView") {
    Dummy dummy{.a = {2, 1, 3}, .num = 3};

    ArrayView array{dummy.a, dummy.num};

    REQUIRE(array.GetNum() == 3);
    REQUIRE(!array.None());

    auto found = array.MinElemIndex([](auto &&l, auto &&r) { return l < r; });

    REQUIRE(found);
    REQUIRE(*found == 1);
}

SCENARIO("ArrayView iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    ArrayView array{dummy.a, dummy.num};

    auto n = 0;
    auto sum = 0;
    for (auto &&i : array) {
        i += 1;
        n++;
        sum += i;
    }

    REQUIRE(n == 6);
    REQUIRE(sum == 2 + 4 + 3 + 1 + 8 + 7 + 6);
}

SCENARIO("ArrayView const iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    Dummy const &constDummy = dummy;

    ArrayView array{constDummy.a, constDummy.num};

    auto n = 0;
    auto sum = 0;
    for (auto &&i : array) {
        n++;
        sum += i;
    }

    REQUIRE(n == 6);
    REQUIRE(sum == 2 + 4 + 3 + 1 + 8 + 7);
}

SCENARIO("ArrayView iterator with Slice") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    for (auto &&i : ArrayView{dummy.a, dummy.num}.From(1)) {
        n++;
        sum += i;
    }

    REQUIRE(n == 5);
    REQUIRE(sum == 4 + 3 + 1 + 8 + 7);
}

SCENARIO("ArrayView Slice index iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.From(1).WithIndex()) {
        n++;
        REQUIRE(n == i);
        sum += elem;
    }

    REQUIRE(n == 5);
    REQUIRE(sum == 4 + 3 + 1 + 8 + 7);
}

SCENARIO("ArrayView full Slice index iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.Slice(1, -2).WithIndex()) {
        n++;
        REQUIRE(n == i);
        sum += elem;
    }

    REQUIRE(n == 4);
    REQUIRE(sum == 4 + 3 + 1 + 8);
}

SCENARIO("ArrayView Slice [2, -2] index iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.Slice(2, -2).WithIndex()) {
        n++;
        REQUIRE(n + 1 == i);
        sum += elem;
    }

    REQUIRE(n == 3);
    REQUIRE(sum == 3 + 1 + 8);
}

SCENARIO("ArrayView Slice [2, -3] index iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.Slice(2, -3).WithIndex()) {
        n++;
        REQUIRE(n + 1 == i);
        sum += elem;
    }

    REQUIRE(n == 2);
    REQUIRE(sum == 3 + 1);
}

SCENARIO("ArrayView Slice [3, -3] index iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.Slice(3, -3).WithIndex()) {
        n++;
        REQUIRE(n + 2 == i);
        sum += elem;
    }

    REQUIRE(n == 1);
    REQUIRE(sum == 1);
}

SCENARIO("ArrayView Slice [3, -4] index iterator") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.Slice(3, -4).WithIndex()) {
        n++;
        sum += elem;
    }

    REQUIRE(n == 0);
    REQUIRE(sum == 0);
}

SCENARIO("ArrayView Slice [1,-1] ForEach") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    ArrayView{dummy.a, dummy.num}.From(1).ForEach([&n, &sum](auto &&elem) {
        n++;
        sum += elem;
    });

    REQUIRE(n == 5);
    REQUIRE(sum == 4 + 3 + 1 + 8 + 7);
}

SCENARIO("ArrayView Slice [1,-2] ForEach") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    auto n = 0;
    auto sum = 0;
    ArrayView{dummy.a, dummy.num}.Slice(1, -2).ForEach([&n, &sum](auto &&elem) {
        n++;
        sum += elem;
    });

    REQUIRE(n == 4);
    REQUIRE(sum == 4 + 3 + 1 + 8);
}

SCENARIO("ArrayView iterator with index") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    Dummy const &constRef = dummy;

    ConstArrayView view{constRef.a, constRef.num};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.From(1).Scope(0xFF).WithIndex()) {
        n++;
        REQUIRE(n == i);
        sum += elem;
    }

    REQUIRE(n == 5);
    REQUIRE(sum == 4 + 3 + 1 + 8 + 7);
}

SCENARIO("ArrayView iterator with excluded scope") {
    Dummy dummy{.a = {2, 4, 3, 1, 8, 7}, .num = 6};

    Dummy const &constRef = dummy;

    ArrayView view{constRef.a, constRef.num};

    auto n = 0;
    auto sum = 0;
    for (auto&&[elem, i] : ArrayView{dummy.a, dummy.num}.From(1).Exclude(0x0F).WithIndex()) {
        n++;
        REQUIRE(n + 3 == i);
        sum += elem;
    }

    REQUIRE(n == 2);
    REQUIRE(sum == 8 + 7);
}

namespace {
    struct UU_Thing {
        int a;
        int b;
    };

    DEF_STRUCT_WRAPPER(Thing, UU_Thing) {
        Thing() {
            a = 10;
            b = 20;
        }

        Thing(int a, int b) {
            this->a = a;
            this->b = b;
        }

        auto GetSize() const -> auto {
            return sizeof(*this);
        }

        auto GetA() const -> auto {
            return a;
        }

        auto GetB() const -> auto {
            return b;
        }
    };

    struct Bar {
        UU_Thing things[10];
        std::size_t num;
    };

    using ThingView = ArrayView<UU_Thing, std::size_t, 20, Thing>;

    auto foo(UU_Thing const &) -> void {

    }

}


SCENARIO("ArrayView with wrapper") {
    Bar bar{.things = {{1, 2},
                    {3, 4},
                    {4, 5}}, .num = 3};

    ThingView view{bar.things, bar.num};

    foo(*view[0]);
    UU_Thing const &uu = view[0].to_struct();

    REQUIRE(view[0].GetSize() == sizeof(Thing));
    REQUIRE(view[0].GetA() == 1);
    REQUIRE(view[1].GetA() == 3);
    REQUIRE(view[2].GetA() == 4);

    auto *p = view.Append(5, 6);
    REQUIRE(p != nullptr);

    REQUIRE(view.GetNum() == 4);
    REQUIRE(view[3].GetA() == 5);
    REQUIRE(view[3].GetB() == 6);
}