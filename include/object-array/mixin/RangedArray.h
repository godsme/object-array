//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_RANGEDARRAY_H
#define OBJECT_ARRAY_RANGEDARRAY_H

#include <object-array/concept/ArrayLike.h>
#include <object-array/mixin/IndexedContainer.h>

namespace mixin {
    template<_concept::ConstArrayLike T>
    class RangedArray : public IndexedContainer<T> {
        using Self = IndexedContainer<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using RangedArrayLike = RangedArray;

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return Self::GetRange(); }
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAY_H
