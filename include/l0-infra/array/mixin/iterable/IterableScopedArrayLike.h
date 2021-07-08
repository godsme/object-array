//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERABLESCOPEDARRAYLIKE_H
#define OBJECT_ARRAY_ITERABLESCOPEDARRAYLIKE_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/iterator/ScopedIterator.h>

namespace mixin {
    template<typename T>
    class IterableScopedArrayLike : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

    protected:
        using Self::IndexBegin;
        using Self::ObjectBegin;
        using Self::ObjectEnd;
        using Self::GetScope;

    private:
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
