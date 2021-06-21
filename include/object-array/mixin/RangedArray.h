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

        auto IndexBegin() const -> auto { return 0; }
        auto IndexEnd() const -> auto { return Self()->GetRange(); }
        auto GetObj(SizeType n) const -> decltype(auto) { return T::ElemToObject(Self()->Elems()[n]); }
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAY_H
