//
// Created by Darwin Yuan on 2021/6/23.
//

#include <cub/base/IntOptional.h>
#include <catch.hpp>

SCENARIO("IntOptional") {
    IntOptional<10> a;

    REQUIRE(!a.has_value());
    REQUIRE(a == std::nullopt);
    REQUIRE(std::nullopt == a);

    a = 7;

    REQUIRE(a.has_value());
    REQUIRE(*a == 7);

    a = std::nullopt;
    REQUIRE(!a.has_value());
    REQUIRE(a == std::nullopt);
    REQUIRE(std::nullopt == a);
    REQUIRE(!(bool)a);

    IntOptional<1000> b{12};
    REQUIRE(b.has_value());
    REQUIRE(*b == 12);

    b.reset();
    REQUIRE(!a.has_value());
    REQUIRE(a == std::nullopt);
    REQUIRE(std::nullopt == a);
}