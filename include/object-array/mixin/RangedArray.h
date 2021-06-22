//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_RANGEDARRAY_H
#define OBJECT_ARRAY_RANGEDARRAY_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/ArrayLike.h>
#include <object-array/mixin/IndexedContainer.h>

namespace mixin {
    __Def_Mixin_Composite(RangedArray, _concept::ConstArrayLike, IndexedContainer) {
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return Self::GetRange(); }
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAY_H
