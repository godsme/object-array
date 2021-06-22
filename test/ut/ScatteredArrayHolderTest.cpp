//
// Created by Darwin Yuan on 2021/6/21.
//

#include <object-array/holder/ScatteredArrayHolder.h>
#include <catch.hpp>

SCENARIO("Int ScatteredArrayHolder") {
    using IntArray = holder::ScatteredArrayHolder<int, 5>;
    IntArray array;

    REQUIRE(array.IndexBegin() == 0);
    REQUIRE(array.IndexEnd() == 5);

    array.Elems()[0] = 1;
    REQUIRE(array.GetObj(0) == 1);
}