//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_7EC4EFF870BF4E2FB73D75B9D05E8BBD
#define OBJECT_ARRAY_2_7EC4EFF870BF4E2FB73D75B9D05E8BBD

#include <l0-infra/base/detail/BinaryOpDetect.h>

namespace mixin {
    template<typename T>
    struct ObjectLess : T {
        auto GetLess() const -> decltype(auto) {
            return (::detail::less::LESS_COMPARE<typename T::ObjectType>);
        }
    };
}

#endif //OBJECT_ARRAY_2_7EC4EFF870BF4E2FB73D75B9D05E8BBD
