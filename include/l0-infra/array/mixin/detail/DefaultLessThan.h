//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_DEFAULTLESSTHAN_H
#define OBJECT_ARRAY_DEFAULTLESSTHAN_H

namespace mixin::detail {
    constexpr auto DEFAULT_LESS_THAN = [](auto&& l, auto&& r) { return l < r; };
    constexpr auto DEFAULT_GREATER_THAN = [](auto&& l, auto&& r) { return r < l; };
}

#endif //OBJECT_ARRAY_DEFAULTLESSTHAN_H
