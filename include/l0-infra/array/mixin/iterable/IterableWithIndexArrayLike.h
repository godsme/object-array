//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLEWITHINDEXARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLEWITHINDEXARRAYLIKE_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/iterator/WithIndexIterator.h>
#include <l0-infra/array/iterator/Iterator.h>

namespace mixin {
    template<typename T>
    struct IterableWithIndexArrayLike : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::ArrayType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetArray;

    public:
        auto begin() const -> auto {
            return iterator::WithIndexIterator{GetArray(), IndexBegin()};
        }

        auto end() const -> auto {
            return iterator::WithIndexIterator{GetArray(), IndexEnd()};
        }

        auto begin() -> auto {
            return iterator::WithIndexIterator{GetArray(), IndexBegin()};
        }

        auto end() -> auto {
            return iterator::WithIndexIterator{GetArray(), IndexEnd()};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEWITHINDEXARRAYLIKE_H
