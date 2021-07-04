//
// Created by Darwin Yuan on 2021/7/4.
//

#ifndef OBJECT_ARRAY_ITERABLEINDEXBASEDARRAY_H
#define OBJECT_ARRAY_ITERABLEINDEXBASEDARRAY_H

#include <l0-infra/array/iterator/IndexBasedIterator.h>

namespace mixin {
    template<typename T>
    class IterableIndexBasedArray : public T {
        using Self = T;

    protected:
        using Self::GetIndices;
        using typename Self::RangedArrayLike;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    private:
        using ConstIterator = iterator::IndexBasedIterator<RangedArrayLike, std::add_const_t<ObjectType>>;
        using Iterator = iterator::IndexBasedIterator<RangedArrayLike, ObjectType>;

    public:
        auto begin() const -> ConstIterator {
            return {*this, GetIndices().IndexBegin()};
        }

        auto end() const -> ConstIterator {
            return {*this, GetIndices().IndexEnd()};
        }

        auto begin() -> Iterator {
            return {*this, GetIndices().IndexBegin()};
        }

        auto end() -> Iterator {
            return {*this, GetIndices().IndexEnd()};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEINDEXBASEDARRAY_H
