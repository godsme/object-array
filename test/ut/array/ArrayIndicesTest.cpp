//
// Created by Darwin Yuan on 2021/6/26.
//

//
// Created by Darwin Yuan on 2021/6/26.
//

#include <l0-infra/array/ArrayIndices.h>
#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

SCENARIO("ArrayIndicesDataHolder Test") {
    using ArrayIndices = ArrayIndices<100>;
    using Array = ObjectArray<int, 90>;
    ArrayIndices indices;
    Array array{1,2,4,5,7,9,3};

    WHEN("Init With an array directly") {
        indices.InitWith(array);
        REQUIRE(indices == ArrayIndices{0, 1, 2, 3, 4, 5, 6});
    }

    WHEN("Init With an array with a scope") {
        indices.InitWith(array, 0x2a); // 101010
        REQUIRE(indices == ArrayIndices{1, 3, 5});
    }
}
