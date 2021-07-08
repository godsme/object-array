//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLEARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLEARRAYLIKE_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/iterator/Iterator.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class IterableArrayLike : public T {
        using Self = T;

    protected:
        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    private:
        using ConstIterator = iterator::Iterator<std::add_const_t<ObjectType>>;
        using Iterator = iterator::Iterator<ObjectType>;

    public:
        auto begin() const -> ConstIterator {
            return {&Self::GetObj(IndexBegin())};
        }

        auto end() const -> ConstIterator {
            return {&Self::GetObj(IndexEnd())};
        }

        auto begin() -> Iterator {
            return {&Self::GetObj(IndexBegin())};
        }

        auto end() -> Iterator {
            return {&Self::GetObj(IndexEnd())};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLEARRAYLIKE_H
