//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_RANGEDARRAY_H
#define OBJECT_ARRAY_RANGEDARRAY_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/ArrayLike.h>

namespace mixin {
    __Def_Mixin(RangedArray, _concept::ConstArrayLike) {
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return Self::GetRange(); }
        auto GetObj(SizeType n) const -> ObjectType const& { return T::ElemToObject(Self::Elems()[n]); }
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAY_H
