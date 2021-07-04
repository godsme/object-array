//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_SIMPLEITERATOR_H
#define OBJECT_ARRAY_SIMPLEITERATOR_H

namespace iterator::detail {
    template<typename, typename>
    class WithIndexIterator;

    template<typename T>
    struct SimpleIterator {
        SimpleIterator(T* p) : p{p} {}

        auto operator!=(SimpleIterator const& rhs) const -> bool { return p != rhs.p; }
        auto operator*() -> T& { return *p; }

    protected:
        auto StepForward() -> void { ++p; }

    private:
        template<typename, typename>
        friend class WithIndexIterator;

    protected:
        T* p;
    };
}

#endif //OBJECT_ARRAY_SIMPLEITERATOR_H
