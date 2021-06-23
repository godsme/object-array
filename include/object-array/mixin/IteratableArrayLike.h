//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERATABLEARRAYLIKE_H
#define OBJECT_ARRAY_ITERATABLEARRAYLIKE_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/RangedArrayLike.h>
#include <object-array/iterator/Iterator.h>

namespace mixin {
    __Def_Mixin(IteratableArrayLike, _concept::RangedArrayLike) {
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        using Self::ObjectBegin;
        using Self::ObjectEnd;

        using ConstIterator = iterator::Iterator<std::add_const_t<ObjectType>>;
        using Iterator = iterator::Iterator<ObjectType>;

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

#endif //OBJECT_ARRAY_ITERATABLEARRAYLIKE_H
