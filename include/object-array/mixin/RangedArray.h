//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_RANGEDARRAY_H
#define OBJECT_ARRAY_RANGEDARRAY_H

#include <object-array/detail/MixinDef.h>
#include <object-array/concept/ArrayLike.h>

namespace mixin {
    template<_concept::ConstArrayLike T>
    __DEF_Array_MIXIN(RangedArray) {
        using Mixin<T>::Self;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return Self()->GetRange(); }
        auto GetObj(SizeType n) const -> ObjectType const& { return T::ElemToObject(Self()->Elems()[n]); }
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAY_H
