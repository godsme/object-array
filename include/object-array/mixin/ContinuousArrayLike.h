//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H

#include <object-array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<_concept::ContinuousArrayLikeDataHolder T>
    struct ContinuousArrayLike : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ElemType;
        using typename T::ObjectType;

        using Self::Elems;
        using Self::ElemToObject;

        auto GetRange() const -> SizeType { return Self::Num(); }
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
