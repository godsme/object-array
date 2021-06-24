//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLEINDEXEDARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLEINDEXEDARRAYLIKE_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/iterator/IndexedIterator.h>
#include <object-array/iterator/Iterator.h>

namespace mixin {
    template<_concept::RangedArrayLike T>
    struct IterableIndexedArrayLike : T {
        using Self = T;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        using Self::IndexBegin;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

        using ConstIterator = iterator::IndexedIterator<std::add_const_t<ObjectType>, SizeType>;
        using Iterator = iterator::IndexedIterator<ObjectType, SizeType>;

        using ConstEndIterator = iterator::Iterator<std::add_const_t<ObjectType>>;
        using EndIterator = iterator::Iterator<ObjectType>;

    public:
        auto begin() const -> ConstIterator {
            return {ObjectBegin(), IndexBegin()};
        }

        auto end() const -> ConstEndIterator {
            return {ObjectEnd()};
        }

        auto begin() -> Iterator {
            return {ObjectBegin(), IndexBegin()};
        }

        auto end() -> EndIterator {
            return {ObjectEnd()};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEINDEXEDARRAYLIKE_H
