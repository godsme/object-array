//
// Created by Darwin Yuan on 2021/6/21.
//

#include <object-array/holder/ObjectArrayHolder.h>
#include <catch.hpp>

SCENARIO("Int ObjectArrayHolder") {
    using IntArray = holder::ObjectArrayHolder<int, 5>;
    IntArray array;

    REQUIRE(array.IndexBegin() == 0);
    REQUIRE(array.IndexEnd() == 0);
    array.num = 1;
    array.elems[0] = 1;
    REQUIRE(array.IndexEnd() == 1);
    REQUIRE(array.GetObj(0) == 1);
}