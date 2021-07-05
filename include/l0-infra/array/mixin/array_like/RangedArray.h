//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_RANGEDARRAY_H
#define OBJECT_ARRAY_RANGEDARRAY_H

#include <l0-infra/array/concept/ArrayLike.h>
#include <l0-infra/array/mixin/array_like/IndexedContainer.h>

namespace mixin {
    template<typename T>
    class RangedArray : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return Self::GetRange(); }
    };
}

#endif //OBJECT_ARRAY_RANGEDARRAY_H
