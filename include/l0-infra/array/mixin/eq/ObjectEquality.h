//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_3D6C25F9943B4B2E945A766211C4F8C1
#define OBJECT_ARRAY_2_3D6C25F9943B4B2E945A766211C4F8C1

#include <l0-infra/base/detail/BinaryOpDetect.h>

namespace mixin {
    template<typename T>
    struct ObjectEquality : T {
        using typename T::ObjectType;

        auto GetEq() const -> decltype(auto) {
            return (::detail::equality::EQ_COMPARE<ObjectType>);
        }
    };
}

#endif //OBJECT_ARRAY_2_3D6C25F9943B4B2E945A766211C4F8C1
