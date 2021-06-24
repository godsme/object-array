//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_INDEXEDREFACCESSOR_H
#define OBJECT_ARRAY_INDEXEDREFACCESSOR_H

#include <object-array/concept/ArrayLike.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    struct IndexedRefAccessor : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        auto operator[](SizeType n) const -> ObjectType const& {
            return Self::GetObj(n + Self::IndexBegin());
        }

        auto operator[](SizeType n) -> ObjectType& {
            return Self::GetObj(n + Self::IndexBegin());
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDREFACCESSOR_H
