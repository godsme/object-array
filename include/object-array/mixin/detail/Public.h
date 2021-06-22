//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_PUBLIC_H
#define OBJECT_ARRAY_PUBLIC_H

namespace mixin::detail {
    template<template<typename, bool> typename MIXIN>
    struct Public {
        template<typename T>
        using Type = MIXIN<T, false>;
    };
}

namespace mixin {
    template<template<typename, bool> typename MIXIN>
    using Public = template detail::Public<MIXIN>::Type;
}

#endif //OBJECT_ARRAY_PUBLIC_H
