//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_C65FF96A7CA3465D97FA2B18B68E39C9
#define OBJECT_ARRAY_2_C65FF96A7CA3465D97FA2B18B68E39C9

#include <l0-infra/array/detail/ArrayIndices.h>
#include <l0-infra/array/iterator/IndicesRandomIterator.h>

namespace detail {
    template<typename ARRAY>
    struct ScopedArrayIndices {
        constexpr static auto MAX_SIZE = ARRAY::MAX_SIZE;
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = typename ARRAY::ObjectType;

        ScopedArrayIndices(ARRAY& array)
            : array{array}
            , indices{array, array.GetScope()} {
        }

        ScopedArrayIndices(ARRAY& array, SizeType from, SizeType until, typename ARRAY::BitMap scope)
            : array{array}
            , indices{from, until, scope} {
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
        ::array_indices::Array<MAX_SIZE> indices;
        ARRAY& array;
    };
}

#endif //OBJECT_ARRAY_2_C65FF96A7CA3465D97FA2B18B68E39C9
