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
    ArrayIndices<100> holder;
    ObjectArray<int, 90> array{1,2,4,5,7,9,3};

    holder.InitWith(array);

    REQUIRE(holder == ArrayIndices<100>{0, 1, 2, 3, 4, 5, 6});
}