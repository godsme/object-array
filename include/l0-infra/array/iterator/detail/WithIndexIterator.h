//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H
#define OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H

#include <l0-infra/array/iterator/detail/SimpleIterator.h>

namespace iterator::detail {
    template<typename ARRAY, typename OBJ_TYPE>
    class WithIndexIterator {
        using SizeType = typename ARRAY::SizeType;
        struct Result {
            OBJ_TYPE& value;
            SizeType const index;
        };

    public:
        WithIndexIterator(ARRAY& array, SizeType from) : array{array}, i{from} {}

        auto operator!=(WithIndexIterator const& rhs) const -> bool { return i != rhs.i; }
        auto operator*() const -> Result { return {array.GetObj(i), i}; }

    protected:
        auto StepForward() -> void { ++i; }

    protected:
        ARRAY& array;
        SizeType i;
    };
}

#endif //OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H
