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

SCENARIO("DynamicArray Clear") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        array.Clear();
        REQUIRE(array.GetNum() == 0);
        REQUIRE(allocator.GetNum() == 0);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray ClearFrom") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        array.ClearFrom(1);
        REQUIRE(array.GetNum() == 1);
        REQUIRE(allocator.GetNum() == 1);
        REQUIRE(array[0] == 10);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray ClearUntil") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        array.ClearUntil(1);
        REQUIRE(array.GetNum() == 1);
        REQUIRE(allocator.GetNum() == 1);
        REQUIRE(array[0] == 20);
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

SCENARIO("DynamicArray Sort") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(20));

        array.DescSort();

        REQUIRE(array[0] == 20);
        REQUIRE(array[1] == 10);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray PartialSort") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 5> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(40));
        REQUIRE(nullptr != array.Append(30));
        REQUIRE(nullptr != array.Append(20));

        auto&& view = array.PartialSort(2);

        REQUIRE(view[0] == 10);
        REQUIRE(view[1] == 20);

        REQUIRE(array[0] == 10);
        REQUIRE(array[1] == 20);
        REQUIRE(array[2] == 40);
        REQUIRE(array[3] == 30);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray SortView PartialSort") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 5> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(40));
        REQUIRE(nullptr != array.Append(30));
        REQUIRE(nullptr != array.Append(20));

        auto&& view = array.SortObject().PartialSort(2);

        REQUIRE(view.GetNum() == 2);
        REQUIRE(view[0] == 10);
        REQUIRE(view[1] == 20);

        REQUIRE(array[0] == 10);
        REQUIRE(array[1] == 40);
        REQUIRE(array[2] == 30);
        REQUIRE(array[3] == 20);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray Replace") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 5> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(40));
        REQUIRE(nullptr != array.Append(30));
        REQUIRE(nullptr != array.Append(20));

        auto* p = array.Replace(1, 50);
        REQUIRE(p != nullptr);
        REQUIRE(*p == 50);

        REQUIRE(array[0] == 10);
        REQUIRE(array[1] == 50);
        REQUIRE(array[2] == 30);
        REQUIRE(array[3] == 20);
    }

    REQUIRE(allocator.GetNum() == 0);
}

SCENARIO("DynamicArray Replace Object") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 5> array{allocator};
        REQUIRE(nullptr != array.Append(10));
        REQUIRE(nullptr != array.Append(40));
        REQUIRE(nullptr != array.Append(30));
        REQUIRE(nullptr != array.Append(20));

        auto* p = array.ReplaceObj(&array[1], 50);
        REQUIRE(p != nullptr);
        REQUIRE(*p == 50);

        REQUIRE(array[0] == 10);
        REQUIRE(array[1] == 50);
        REQUIRE(array[2] == 30);
        REQUIRE(array[3] == 20);
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

SCENARIO("DynamicArray MinElem") {
    ScatteredArray<int, 10> allocator;
    {
        DynamicArray<ScatteredArray<int, 10>, 2> array{allocator};
        REQUIRE(nullptr != array.Append(20));
        REQUIRE(nullptr != array.Append(10));

        auto* min = array.MinElem();
        REQUIRE(min != nullptr);
        REQUIRE(*min == 10);

        auto index = array.MinElemIndex();
        REQUIRE(index.has_value());
        REQUIRE(*index == 1);
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