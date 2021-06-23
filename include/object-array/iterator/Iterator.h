//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_ITERATOR_H
#define OBJECT_ARRAY_ITERATOR_H

namespace iterator {
    template<typename, typename>
    class IndexedIterator;

    template<typename T>
    struct Iterator {
        Iterator(T* p) : p{p} {}

        auto operator++() -> Iterator& {
            ++p;
            return *this;
        }

        auto operator!=(Iterator const& rhs) const -> bool { return p != rhs.p; }
        auto operator*() -> T& { return *p; }

    private:
        template<typename, typename>
        friend class IndexedIterator;

    private:
        T* p;
    };
}

#endif //OBJECT_ARRAY_ITERATOR_H
