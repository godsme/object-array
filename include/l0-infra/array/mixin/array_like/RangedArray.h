//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_RANGEDARRAY_H
#define OBJECT_ARRAY_RANGEDARRAY_H

#include <l0-infra/array/concept/ArrayLike.h>
#include <l0-infra/array/mixin/array_like/IndexedContainer.h>

namespace mixin {
    template<__cOnCePt(ConstArrayLike) T>
    class RangedArray : public IndexedContainer<T> {
        using Self = IndexedContainer<T>;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    protected:
        using RangedArrayLike = RangedArray;

    public:
        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return Self::GetRange(); }
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAY_H
