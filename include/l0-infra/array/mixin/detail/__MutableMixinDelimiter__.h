//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY___MUTABLEMIXINDELIMITER___H
#define OBJECT_ARRAY___MUTABLEMIXINDELIMITER___H

namespace mixin {
    template<typename T>
    struct __MutableMixinDelimiter__ final : T {
        constexpr static bool IS_CONST = T::CONST;
    };
}

#endif //OBJECT_ARRAY___MUTABLEMIXINDELIMITER___H
