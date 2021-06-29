//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H

#include <l0-infra/array/concept/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ContinuousArrayLikeDataHolder) T>
    struct ContinuousArrayLike : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ElemType;
        using typename T::ObjectType;

    protected:
        using Self::Elems;
        using Self::ElemToObject;

    public:
        auto GetRange() const -> SizeType { return Self::Num(); }
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
