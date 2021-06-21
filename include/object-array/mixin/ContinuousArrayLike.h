//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H

#include <object-array/detail/MixinDef.h>
#include <object-array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<_concept::ContinuousArrayLikeDataHolder T>
    __DEF_Array_MIXIN(ContinuousArrayLike) {
        using Mixin<T>::Self;
    public:
        using SizeType = typename T::SizeType;
        using ElemType = typename T::ElemType;
        using ObjectType = typename T::ObjectType;

        auto Elems() const -> ElemType const* { return Self()->elems; }
        static auto ElemToObject(ElemType const& elem) -> ObjectType const& { return T::ElemToObject(elem); }
        auto GetRange() const -> SizeType { return Self()->num; }
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
