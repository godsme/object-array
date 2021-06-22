//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    __Def_Mixin(ContinuousArrayLike, _concept::ContinuousArrayLikeDataHolder) {
    public:
        using SizeType = typename T::SizeType;
        using ElemType = typename T::ElemType;
        using ObjectType = typename T::ObjectType;

        using Self::Elems;
        using Self::ElemToObject;

        auto GetRange() const -> SizeType { return Self::Num(); }
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H