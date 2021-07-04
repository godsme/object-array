//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLEWITHINDEXARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLEWITHINDEXARRAYLIKE_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/iterator/WithIndexIterator.h>
#include <l0-infra/array/iterator/Iterator.h>

namespace mixin {
    template<__cOnCePt(RangedArrayLike) T>
    struct IterableWithIndexArrayLike : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        using Self::IndexBegin;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

        using ConstIterator = iterator::WithIndexIterator<std::add_const_t<ObjectType>, SizeType>;
        using Iterator = iterator::WithIndexIterator<ObjectType, SizeType>;

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

#endif //OBJECT_ARRAY_ITERABLEWITHINDEXARRAYLIKE_H
