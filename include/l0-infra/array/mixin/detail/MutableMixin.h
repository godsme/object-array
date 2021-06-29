//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_MUTABLEMIXIN_H
#define OBJECT_ARRAY_MUTABLEMIXIN_H

#include <l0-infra/array/mixin/detail/Mixins.h>

namespace mixin::detail {
    template<typename T>
    struct DummyMixin : T {
        constexpr static bool IS_CONST = T::IS_CONST;
    };

    template<typename T, bool = DummyMixin<T>::IS_CONST, template <typename> typename ... MIXINS>
    struct MutableTrait {
        using Type = T;
    };

    template<typename T, template <typename> typename ... MIXINS>
    struct MutableTrait<T, false, MIXINS...> {
        using Type = typename Mixins<MIXINS...>::template Mixin<T>;
    };


}

namespace mixin {
    template<template<typename> typename ... MIXINS>
    struct Mutable {
        template<typename T>
        using AsMixin = typename detail::MutableTrait<T, detail::DummyMixin<T>::IS_CONST, MIXINS...>::Type;
    };
}

#endif //OBJECT_ARRAY_MUTABLEMIXIN_H
