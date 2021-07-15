//
// Created by Darwin Yuan on 2021/7/9.
//

#include <l0-infra/array/holder/ScatteredArrayHolder.h>
#include <l0-infra/array/ScatteredArray.h>
#include <catch.hpp>

namespace {
    using ConstIntHolder = holder::ScatteredArrayHolder<int const, 10>;
    static_assert(std::is_trivially_destructible_v<ConstIntHolder>);

    template<typename T>
    struct Array : T {
        using T::T;
        Array() {}

        using T::elems;
        using T::occupied;
    };
}

SCENARIO("should be able to construct with init-list") {
    Array<ConstIntHolder> holder{1,2,3};

    REQUIRE(holder.occupied.count() == 3);
    REQUIRE(holder.occupied[0]);
    REQUIRE(holder.occupied[1]);
    REQUIRE(holder.occupied[2]);

    REQUIRE(*holder.elems[0] == 1);
    REQUIRE(*holder.elems[1] == 2);
    REQUIRE(*holder.elems[2] == 3);

    static_assert(!std::is_copy_assignable_v<ConstIntHolder>);
    static_assert(!std::is_move_assignable_v<ConstIntHolder>);
}

namespace {
    using IntHolder = holder::ScatteredArrayHolder<int, 10>;
    static_assert(std::is_trivially_destructible_v<IntHolder>);

    static_assert(std::is_copy_assignable_v<IntHolder>);
    static_assert(std::is_move_assignable_v<IntHolder>);

    template<typename T>
    struct ScatteredArray : T, scattered_array::Private::Type<T, ScatteredArray<T>> {
        using T::T;
        ScatteredArray() {}
    };
}
