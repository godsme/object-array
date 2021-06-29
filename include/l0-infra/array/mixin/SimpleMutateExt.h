//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SIMPLEMUTATEEXT_H
#define OBJECT_ARRAY_SIMPLEMUTATEEXT_H

#include <l0-infra/array/concept/SimpleMutable.h>

namespace mixin {
    template<__cOnCePt(SimpleMutable) T>
    class SimpleMutateExt : public T {
        using Self = T;
    public:
        using typename Self::ObjectType;

    protected:
        using Self::GetObjIndex;

    public:
        auto Remove(ObjectType const * p) -> void {
            auto index = GetObjIndex(p);
            if (index) Self::Erase(*index);
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMUTATEEXT_H
