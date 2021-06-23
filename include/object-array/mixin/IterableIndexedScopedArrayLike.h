//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLEINDEXEDSCOPEDARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLEINDEXEDSCOPEDARRAYLIKE_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/iterator/IndexedIterator.h>
#include <object-array/iterator/IndexedScopedIterator.h>

namespace mixin {
    template<_concept::ScopedRangedArrayLike T>
    struct IterableIndexedScopedArrayLike : detail::Extends<T> {
        using Self = detail::Extends<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using BitMap = typename T::BitMap;

        using Self::GetScope;
        using Self::IndexBegin;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

        using ConstIterator = iterator::IndexedScopedIterator<std::add_const_t<ObjectType>, BitMap, SizeType>;
        using Iterator = iterator::IndexedScopedIterator<ObjectType, BitMap, SizeType>;

        using EndIterator = iterator::EmptyIterator;

    public:
        auto begin() const -> ConstIterator {
            return {ObjectBegin(), GetScope(), IndexBegin()};
        }

        auto end() const -> EndIterator {
            return {};
        }

        auto begin() -> Iterator {
            return {ObjectBegin(), GetScope(), IndexBegin()};
        }

        auto end() -> EndIterator {
            return {};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEINDEXEDSCOPEDARRAYLIKE_H
