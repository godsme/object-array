//
// Created by Darwin Yuan on 2021/7/5.
//

#include <l0-infra/array/ScatteredArray.h>
#include <l0-infra/array/DynamicArray.h>
#include <catch.hpp>

SCENARIO("DynamicArray Append") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(allocator.GetNum() == 1);
        REQUIRE(nullptr != array.Append(20));
        REQUIRE(allocator.GetNum() == 2);
        REQUIRE(nullptr == array.Append(30));
    }
    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray Erase") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        array.Erase(1);
        REQUIRE(array.GetNum() == 1);
        REQUIRE(array[0] == 10);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray Remove") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        array.Remove(&array[1]);
        REQUIRE(array.GetNum() == 1);
        REQUIRE(array[0] == 10);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray Iterable") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        auto sum = 0;
        auto n = 0;
        for(auto&& item : array) {
            n++;
            sum += item;
        }
        REQUIRE(sum == 30);
        REQUIRE(n == 2);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray Iterable with index") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        auto sum = 0;
        auto n = 0;
        for(auto&& [item, i] : array.WithIndex()) {
            REQUIRE(n == i);
            n++;
            sum += item;
        }
        REQUIRE(sum == 30);
        REQUIRE(n == 2);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray Find") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        auto* found = array.Find(10);
        REQUIRE(found != nullptr);
        REQUIRE(*found == 10);

        auto index = array.FindIndex(20);
        REQUIRE(index.has_value());
        REQUIRE(*index == 1);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray ForEach") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        auto sum = 0;
        auto n = 0;
        array.ForEach([&](auto&& item) {
            n++;
            sum += item;
        });
        REQUIRE(sum == 30);
        REQUIRE(n == 2);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray copy construct") {
    ScatteredArray<int, 10> allocator;
    using IntArray = DynamicArray<ScatteredArray<int, 10>, 2>;
    {
        IntArray array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));
        REQUIRE(allocator.GetNum() == 2);
        IntArray array2 = array;
        REQUIRE(allocator.GetNum() == 4);
        REQUIRE(array2.GetNum() == 2);
        REQUIRE(array2[0] == 10);
        REQUIRE(array2[1] == 20);
        REQUIRE(array2.All());
    }
    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray copy assignment") {
    ScatteredArray<int, 10> allocator;
    using IntArray = DynamicArray<ScatteredArray<int, 10>, 2>;
    {
        IntArray array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));
        REQUIRE(allocator.GetNum() == 2);
        IntArray array2{allocator};
        REQUIRE(nullptr != array2.Append(30));
        REQUIRE(allocator.GetNum() == 3);
        REQUIRE(array2.GetNum() == 1);
        REQUIRE(array2[0] == 30);
        array2 = array;
        REQUIRE(allocator.GetNum() == 4);
        REQUIRE(array2.GetNum() == 2);
        REQUIRE(array2[0] == 10);
        REQUIRE(array2[1] == 20);
    }
    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray move construct") {
    ScatteredArray<int, 10> allocator;
    using IntArray = DynamicArray<ScatteredArray<int, 10>, 2>;
    {
        IntArray array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        REQUIRE(allocator.GetNum() == 2);
        IntArray array2 = std::move(array);
        REQUIRE(allocator.GetNum() == 2);
    }

    REQUIRE(allocator.GetNum() == 0);

}