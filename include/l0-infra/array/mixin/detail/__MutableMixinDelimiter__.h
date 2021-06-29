//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY___MUTABLEMIXINDELIMITER___H
#define OBJECT_ARRAY___MUTABLEMIXINDELIMITER___H

namespace mixin::detail {
    template<typename T>
    struct DummyMixin : T {
        constexpr static bool IS_CONST = T::IS_CONST;
    };
}

namespace mixin {
    template<typename T, bool = detail::DummyMixin<T>::IS_CONST >
    struct __MutableMixinDelimiter__ : T {};

    template<typename T>
    struct __MutableMixinDelimiter__<T, true> final : T {};
}

#endif //OBJECT_ARRAY___MUTABLEMIXINDELIMITER___H
