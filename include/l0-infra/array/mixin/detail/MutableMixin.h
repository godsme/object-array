//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_MUTABLEMIXIN_H
#define OBJECT_ARRAY_MUTABLEMIXIN_H

namespace mixin::detail {
    template<typename T>
    struct DummyMixin : T {
        constexpr static bool IS_CONST = T::IS_CONST;
    };

    template<template<typename> typename MIXIN, typename T, bool = DummyMixin<T>::IS_CONST>
    struct MutableTrait {
        using Type = T;
    };

    template<template<typename> typename MIXIN, typename T>
    struct MutableTrait<MIXIN, T, false> {
        using Type = MIXIN<T>;
    };

    template<template<typename> typename MIXIN>
    struct Mutable {
        template<typename T>
        using Mixin = typename MutableTrait<MIXIN, T>::Type;
    };
}

#endif //OBJECT_ARRAY_MUTABLEMIXIN_H
