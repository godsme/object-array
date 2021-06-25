//
// Created by Darwin Yuan on 2021/6/25.
//

#include <l0-infra/base/DeduceSizeType.h>
#include <catch.hpp>

SCENARIO("DeduceSizeType") {
    static_assert(std::is_same_v<DeduceSizeType_t<0>, uint8_t>);
    static_assert(std::is_same_v<DeduceSizeType_t<255>, uint8_t>);
    static_assert(std::is_same_v<DeduceSizeType_t<256>, uint16_t>);
    static_assert(std::is_same_v<DeduceSizeType_t<65535>, uint16_t>);
    static_assert(std::is_same_v<DeduceSizeType_t<65536>, uint32_t>);
}