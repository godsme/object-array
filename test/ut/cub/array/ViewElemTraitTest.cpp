//
// Created by Darwin Yuan on 2021/6/25.
//

#include <object-array/holder/detail/ViewElemTrait.h>
#include <l0-infra/base/StructWrapper.h>
#include <catch.hpp>

namespace {
    struct Foo {
        int a;
    };

    DEF_STRUCT_WRAPPER(FooW, Foo) {
    auto GetA() const -> auto {
        return a;
    }
};
}

SCENARIO("ViewElemTrait Same") {
    using Trait = holder::detail::ViewElemTrait_T<Foo, Foo>;
    REQUIRE(Trait::ConstObjToElem(Foo{10}).a == 10);
    REQUIRE(Trait::ConstObjToElem(Foo{13}).a == 13);
}

SCENARIO("ViewElemTrait Diff") {
    using Trait = holder::detail::ViewElemTrait_T<Foo, FooW>;

    REQUIRE(Trait::ConstObjToElem(Foo{10}).GetA() == 10);
    REQUIRE(Trait::ConstObjToElem(Foo{13}).GetA() == 13);
}