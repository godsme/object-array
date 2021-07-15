//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_FB89D4C9551947FBBCB5FFA606688350
#define OBJECT_ARRAY_2_FB89D4C9551947FBBCB5FFA606688350

#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct ViewedScope : T {
        using typename T::BitMap;

    public:
        auto GetScope() const -> BitMap {
            return T::GetArray().GetScope();
        }
    };
}

#endif //OBJECT_ARRAY_2_FB89D4C9551947FBBCB5FFA606688350
