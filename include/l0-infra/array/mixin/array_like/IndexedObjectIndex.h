//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_INDEXEDOBJECTINDEX_H
#define OBJECT_ARRAY_INDEXEDOBJECTINDEX_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/RangedArrayLike.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class IndexedObjectIndex : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        using typename Self::Maybe;

        using Self::GetObj;
        using Self::IndexBegin;
        using Self::GetIndices;

    public:
        auto GetObjIndex(ObjectType const *obj) -> Maybe {
            auto *base = reinterpret_cast<ObjectType const *>(Self::Elems() + IndexBegin());
            return obj < base ? std::nullopt : GetIndices().FindIndex(obj - base);
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDOBJECTINDEX_H
