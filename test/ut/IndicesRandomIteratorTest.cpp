//
// Created by Darwin Yuan on 2021/7/13.
//

#include <l0-infra/array/iterator/IndicesRandomIterator.h>
#include <catch.hpp>

namespace {
    struct Array {
        int a[10];
        using SizeType = uint8_t;
        using ObjectType = int;
        auto GetObject(SizeType n) -> ObjectType& {
            return a[n];
        }
    };

}
SCENARIO("IndicesRandomIterator") {
    Array array{.a = {7,8,3,2,5,9,4,0,1}};
    uint8_t b[4] = {1,3,5,7};

    iterator::IndicesRandomIterator begin{b, array};
    iterator::IndicesRandomIterator end{b + 4, array};

    std::sort(begin, end);

    REQUIRE(array.a[1] == 0);
    REQUIRE(array.a[3] == 2);
    REQUIRE(array.a[5] == 8);
    REQUIRE(array.a[7] == 9);
}