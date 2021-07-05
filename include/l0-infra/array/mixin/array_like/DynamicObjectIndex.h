//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_DYNAMICOBJECTINDEX_H
#define OBJECT_ARRAY_DYNAMICOBJECTINDEX_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/RangedArrayLike.h>

namespace mixin {
    template<typename T>
    class DynamicObjectIndex : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::Maybe;

        using Self::GetPointers;

    public:
        auto GetObjIndex(ObjectType const *obj) const -> Maybe {
            return GetPointers().FindIndex(const_cast<ObjectType*>(obj));
        }
    };
}

#endif //OBJECT_ARRAY_DYNAMICOBJECTINDEX_H
