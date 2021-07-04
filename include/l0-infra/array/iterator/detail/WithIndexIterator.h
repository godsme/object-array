//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H
#define OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H

#include <l0-infra/array/iterator/detail/SimpleIterator.h>

namespace iterator::detail {
    template<typename T, typename SIZE_TYPE>
    class WithIndexIterator {
        struct Result {
            T& value;
            SIZE_TYPE const index;
        };

    public:
        WithIndexIterator(T* p, SIZE_TYPE from) : p{p}, i{from} {}

        auto operator!=(WithIndexIterator const& rhs) const -> bool { return p != rhs.p; }
        auto operator!=(SimpleIterator<T> const& rhs) const -> bool { return p != rhs.p; }
        auto operator*() const -> Result { return {*p, i}; }

    protected:
        auto StepForward() -> void { ++p, ++i; }

    protected:
        T* p;
        SIZE_TYPE i;
    };
}

#endif //OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H