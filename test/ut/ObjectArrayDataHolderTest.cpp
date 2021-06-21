//
// Created by Darwin Yuan on 2021/6/21.
//

#include <object-array/holder/ObjectArrayDataHolder.h>
#include <catch.hpp>

SCENARIO("ObjectArrayDataHolder") {
    using IntArray = holder::ObjectArrayDataHolder<int, 5>;
    static_assert(std::is_same_v<int, IntArray::ObjectType>);
    static_assert(std::is_same_v<int, IntArray::ElemType>);
    static_assert(5 == IntArray::MAX_SIZE);

    static_assert(!std::is_trivially_default_constructible_v<IntArray>);
    static_assert(std::is_trivially_destructible_v<IntArray>);

    IntArray array;
    REQUIRE(array.num == 0);

    array.elems[0] = 1;

    REQUIRE(IntArray::ElemToObject(array.elems[0]) == 1);
}
