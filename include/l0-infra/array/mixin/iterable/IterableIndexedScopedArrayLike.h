//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLEINDEXEDSCOPEDARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLEINDEXEDSCOPEDARRAYLIKE_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/iterator/WithIndexIterator.h>
#include <l0-infra/array/iterator/WithIndexScopedIterator.h>

namespace mixin {
    template<__cOnCePt(ScopedRangedArrayLike) T>
    struct IterableIndexedScopedArrayLike : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

        using Self::GetScope;
        using Self::IndexBegin;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

        using ConstIterator = iterator::IndexedScopedIterator<std::add_const_t<ObjectType>, BitMap, SizeType>;
        using Iterator = iterator::IndexedScopedIterator<ObjectType, BitMap, SizeType>;

        using EndIterator = iterator::EmptyIterator;

    public:
        auto begin() const -> ConstIterator {
            return {GetScope() >> IndexBegin(), ObjectBegin(), IndexBegin()};
        }

        auto end() const -> EndIterator {
            return {};
        }

        auto begin() -> Iterator {
            return {GetScope() >> IndexBegin(), ObjectBegin(), IndexBegin()};
        }

        auto end() -> EndIterator {
            return {};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEINDEXEDSCOPEDARRAYLIKE_H
