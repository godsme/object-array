//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_ITERABLEARRAYINDICES_H
#define OBJECT_ARRAY_ITERABLEARRAYINDICES_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/iterator/IndicesRandomIterator.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class IterableArrayIndices : public T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        using Self::GetObj;
        using Self::IndexBegin;
        using Self::IndexEnd;

        using ConstIterator = iterator::IndicesRandomIterator<std::add_const_t<ObjectType>>;
        using Iterator = iterator::IndicesRandomIterator<ObjectType>;

    public:
        auto begin() const -> ConstIterator {
            return {ObjectBegin()};
        }

        auto end() const -> ConstIterator {
            return {ObjectEnd()};
        }

        auto begin() -> Iterator {
            return {ObjectBegin()};
        }

        auto end() -> Iterator {
            return {ObjectEnd()};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEARRAYINDICES_H
