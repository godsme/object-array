//
// Created by Darwin Yuan on 2021/6/26.
//

#include <l0-infra/array/ArraySortObject.h>
#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

SCENARIO("ArraySortObject Test") {
    using Array = ObjectArray<int, 90>;
    using ArraySortObject = ArraySortObject<Array>;
    Array array{3,2,4,1};


    WHEN("array itself should be able to sort") {
        array.Sort();
        REQUIRE(array[0] == 1);
        REQUIRE(array[1] == 2);
        REQUIRE(array[2] == 3);
        REQUIRE(array[3] == 4);
    }

    WHEN("should be able to sort by sort object") {
        ArraySortObject sorted{array};
        sorted.Sort();
        REQUIRE(sorted[0] == 1);
        REQUIRE(sorted[1] == 2);
        REQUIRE(sorted[2] == 3);
        REQUIRE(sorted[3] == 4);
    }
}