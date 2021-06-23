//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H
#define OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H

#include <object-array/iterator/Iterator.h>

namespace iterator::detail {
    template<typename T, typename SIZE_TYPE>
    class IndexedIterator {
        struct Result {
            T& value;
            SIZE_TYPE index;
        };

    public:
        IndexedIterator(T* p, SIZE_TYPE from) : p{p}, i{from} {}

        auto operator!=(IndexedIterator const& rhs) const -> bool { return p != rhs.p; }
        auto operator!=(Iterator<T> const& rhs) const -> bool { return p != rhs.p; }
        auto operator*() const -> Result { return {*p, i}; }

    protected:
        auto Forward() -> void {
            ++p, ++i;
        }

    protected:
        T* p;
        SIZE_TYPE i;
    };
}

#endif //OBJECT_ARRAY_DETAIL_INDEXEDITERATOR_H
