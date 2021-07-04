//
// Created by Darwin Yuan on 2021/6/29.
//

#ifndef OBJECT_ARRAY_OBJECTINDEX_H
#define OBJECT_ARRAY_OBJECTINDEX_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/RangedArrayLike.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class ObjectIndex : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        using typename Self::Maybe;

        using Self::GetObj;
        using Self::IndexBegin;

    public:
        auto GetObjIndex(ObjectType const *obj) -> Maybe {
            auto *base = &GetObj(IndexBegin());
            return obj < base ? std::nullopt : Maybe(obj - base);
        }
    };
}

#endif //OBJECT_ARRAY_OBJECTINDEX_H
