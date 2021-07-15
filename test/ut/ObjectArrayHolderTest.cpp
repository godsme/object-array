//
// Created by Darwin Yuan on 2021/7/8.
//

#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

namespace {
    using ConstIntHolder = holder::ObjectArrayHolder<int const, 10>;
    static_assert(std::is_trivially_destructible_v<ConstIntHolder>);

    template<typename T>
    struct Array : T, object_array::Private::Type<T, Array<T>> {
        using T::T;
        Array() {}
    };

    static_assert(std::is_trivially_destructible_v<Array<ConstIntHolder>>);

    using IntHolder = holder::ObjectArrayHolder<int, 10>;
    static_assert(std::is_trivially_destructible_v<IntHolder>);
}

SCENARIO("Const Holder cannot copy/move assignment") {
    static_assert(!std::is_copy_assignable_v<ConstIntHolder>);
    static_assert(!std::is_move_assignable_v<ConstIntHolder>);
    static_assert(ConstIntHolder::IS_CONST);

    Array<ConstIntHolder> array{1,2,3,4};
    REQUIRE(4 == array.Num());

    REQUIRE(array.IndexBegin() == 0);
    REQUIRE(array.IndexEnd() == 4);

    REQUIRE(array.GetObject(0) == 1);
    REQUIRE(array.GetObject(1) == 2);
    REQUIRE(array.GetObject(2) == 3);
    REQUIRE(array.GetObject(3) == 4);

    WHEN("copy construct") {
        Array<ConstIntHolder> array1 = array;
        REQUIRE(array.Num() == 4);
        REQUIRE(array1.Num() == 4);
    }

    WHEN("copy construct from non-const") {
        Array<IntHolder> array1{1,2,3,4};
        Array<ConstIntHolder> array2 = array1;
        REQUIRE(array1.Num() == 4);
        REQUIRE(array2.Num() == 4);
    }

    WHEN("move construct") {
        Array<ConstIntHolder> array2 = std::move(array);
        REQUIRE(array.Num() == 0);
        REQUIRE(array2.Num() == 4);
    }

    WHEN("move construct from non-const") {
        Array<IntHolder> array1{1,2,3,4};
        Array<ConstIntHolder> array2 = std::move(array1);
        REQUIRE(array1.Num() == 0);
        REQUIRE(array2.Num() == 4);
    }
}

SCENARIO("NonConst Holder should be able to copy/move assignment") {
    static_assert(std::is_copy_assignable_v<IntHolder>);
    static_assert(std::is_move_assignable_v<IntHolder>);

    static_assert(!IntHolder::IS_CONST);

    Array<IntHolder> array{1,2,3,4};
    REQUIRE(4 == array.Num());

    REQUIRE(array.IndexBegin() == 0);
    REQUIRE(array.IndexEnd() == 4);

    REQUIRE(array.GetObject(0) == 1);
    REQUIRE(array.GetObject(1) == 2);
    REQUIRE(array.GetObject(2) == 3);
    REQUIRE(array.GetObject(3) == 4);

    WHEN("copy construct") {
        Array<IntHolder> array1 = array;
        REQUIRE(array.Num() == 4);
        REQUIRE(array1.Num() == 4);
    }

    WHEN("copy construct from const") {
        Array<ConstIntHolder> array1{1,2,3,4};
        Array<IntHolder> array2 = array1;
        REQUIRE(array1.Num() == 4);
        REQUIRE(array2.Num() == 4);
    }

    WHEN("move construct") {
        Array<IntHolder> array2 = std::move(array);
        REQUIRE(array.Num() == 0);
        REQUIRE(array2.Num() == 4);
    }

    WHEN("move construct from const") {
        Array<ConstIntHolder> array1{1,2,3,4};
        Array<IntHolder> array2 = std::move(array1);
        REQUIRE(array1.Num() == 0);
        REQUIRE(array2.Num() == 4);
    }

//    WHEN("Erase") {
//        array.Erase(1);
//
//        REQUIRE(3 == array.Num());
//
//        REQUIRE(array.IndexBegin() == 0);
//        REQUIRE(array.IndexEnd() == 3);
//
//        REQUIRE(array.GetObject(0) == 1);
//        REQUIRE(array.GetObject(1) == 4);
//        REQUIRE(array.GetObject(2) == 3);
//    }
}

SCENARIO("ObjectArray MinElems Elems") {
    ObjectArray<int, 10> array{2,8,1,7,3,5};

    auto&& elems = array.MinElems(3);
    REQUIRE(elems.GetNum() == 3);
    REQUIRE(elems[0] == 1);
    REQUIRE(elems[1] == 2);
    REQUIRE(elems[2] == 3);
}

SCENARIO("ObjectArray SortView") {
    ObjectArray<int, 10> array{2,8,1,7,3,5};

    auto&& view = array.SortView();
    view.MinElems(2);
    REQUIRE(view.GetNum() == 2);
    REQUIRE(view[0] == 1);
    REQUIRE(view[1] == 2);
}

SCENARIO("ObjectArray range-for") {
    ObjectArray<int, 10> array{2,8,1,7,3,5};

    auto n = 0;
    for(auto&& elem : array) {
        n++;
    }
    REQUIRE(n == 6);

    n = 0;
    for(auto&& [elem, i] : array.WithIndex()) {
        REQUIRE(n == i);
        ++n;
    }
    REQUIRE(n == 6);
}