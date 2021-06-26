//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_SCOPEDARRAYINDICES_H
#define OBJECT_ARRAY_SCOPEDARRAYINDICES_H

#include <l0-infra/array/detail/ArrayIndices.h>
#include <l0-infra/array/iterator/IndicesRandomIterator.h>
#include <l0-infra/array/concept/ScopedArrayLike.h>

namespace detail {
    template<__cOnCePt(SimpleScopedRangedArrayLike) ARRAY>
    struct ScopedArrayIndices {
        constexpr static auto MAX_SIZE = ARRAY::MAX_SIZE;
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = typename ARRAY::ObjectType;

        ScopedArrayIndices(ARRAY& array) : array{array} {
            indices.InitWithRange(array, array.GetScope());
        }

        auto begin() -> iterator::IndicesRandomIterator<ARRAY> {
            return {&indices[0], array};
        }

        auto end() -> iterator::IndicesRandomIterator<ARRAY> {
            return {&indices[indices.GetNum()], array};
        }

        auto GetNum() const -> SizeType {
            return indices.GetNum();
        }

    private:
        ::detail::ArrayIndices<MAX_SIZE> indices;
        ARRAY& array;
    };
}

#endif //OBJECT_ARRAY_SCOPEDARRAYINDICES_H
