//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLEWITHINDEXSCOPEDARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLEWITHINDEXSCOPEDARRAYLIKE_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/iterator/WithIndexIterator.h>
#include <l0-infra/array/iterator/WithIndexScopedIterator.h>

namespace mixin {
    template<__cOnCePt(ScopedRangedArrayLike) T>
    struct IterableWithIndexScopedArrayLike : T {
        using Self = T;
    public:
        using typename T::ArrayType;
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

        using Self::GetScope;
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetArray;

        using ConstIterator = iterator::IndexedScopedIterator<ArrayType, BitMap, std::add_const_t<ObjectType>>;
        using Iterator = iterator::IndexedScopedIterator<ArrayType, BitMap, ObjectType>;

        using EndIterator = iterator::EmptyIterator;

    public:
        auto begin() const -> ConstIterator {
            return {GetScope() >> IndexBegin(), GetArray(), IndexBegin()};
        }

        auto end() const -> EndIterator {
            return {};
        }

        auto begin() -> Iterator {
            return {GetScope() >> IndexBegin(), GetArray(), IndexBegin()};
        }

        auto end() -> EndIterator {
            return {};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEWITHINDEXSCOPEDARRAYLIKE_H
