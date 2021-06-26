//
// Created by Darwin Yuan on 2021/6/26.
//

#include <l0-infra/array/ArraySortObject.h>
#include <l0-infra/array/ObjectArray.h>
#include <catch.hpp>

SCENARIO("ArraySortObject Test") {
    using Array = ObjectArray<int, 90>;
    using ArraySortObject = ArraySortObject<Array>;
    Array array{1,2,4,5,7,9,3};
    ArraySortObject sorted{array};
}