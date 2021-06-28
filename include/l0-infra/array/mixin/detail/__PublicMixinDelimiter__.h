//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY___PUBLICMIXINDELIMITER___H
#define OBJECT_ARRAY___PUBLICMIXINDELIMITER___H

namespace mixin::detail {
    template<typename T>
    struct __PublicMixinDelimiter__ : protected T {};
}

#endif //OBJECT_ARRAY___PUBLICMIXINDELIMITER___H
