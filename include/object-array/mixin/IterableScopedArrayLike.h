//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLESCOPEDARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLESCOPEDARRAYLIKE_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/iterator/ScopedIterator.h>

namespace mixin {
    template<_concept::ScopedRangedArrayLike T>
    class IterableScopedArrayLike : public T {
        using Self = T;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using BitMap = typename T::BitMap;

        using Self::IndexBegin;
        using Self::ObjectBegin;
        using Self::ObjectEnd;
        using Self::GetScope;

        using ConstIterator = iterator::ScopedIterator<std::add_const_t<ObjectType>, BitMap>;
        using Iterator = iterator::ScopedIterator<ObjectType, BitMap>;

        using EndIterator = iterator::EmptyIterator;

    public:
        auto begin() const -> ConstIterator {
            return {GetScope() >> IndexBegin(), ObjectBegin()};
        }

        auto end() const -> EndIterator {
            return {};
        }

        auto begin() -> Iterator {
            return {GetScope() >> IndexBegin(), ObjectBegin()};
        }

        auto end() -> EndIterator {
            return {};
        }
    };
}

#endif //OBJECT_ARRAY_ITERABLESCOPEDARRAYLIKE_H
