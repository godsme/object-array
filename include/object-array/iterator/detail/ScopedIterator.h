//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_DETAIL_SCOPEDITERATOR_H
#define OBJECT_ARRAY_DETAIL_SCOPEDITERATOR_H

#include <object-array/iterator/EmptyIterator.h>

namespace iterator::detail {
    template<typename BASE, typename BIT_MAP>
    class ScopedIterator : public BASE {
        auto StepForward() -> void { bitmap >>= 1; BASE::StepForward(); }

        auto ForwardTo1stPresent() {
            while(!bitmap[0] && bitmap.any()) StepForward();
            if(bitmap.none()) BASE::p = nullptr;
        }

    public:
        template<typename ... ARGS>
        ScopedIterator(BIT_MAP const& bitmap, ARGS&& ... args)
                : bitmap{bitmap}, BASE{std::forward<ARGS>(args)...} { ForwardTo1stPresent(); }

        auto operator++() -> ScopedIterator& {
            StepForward();
            ForwardTo1stPresent();
            return (*this);
        }

        auto operator!=(EmptyIterator const& rhs) const -> bool { return BASE::p != nullptr; }

        ScopedIterator() = delete;
        ScopedIterator(ScopedIterator const&) = delete;
        ScopedIterator(ScopedIterator&&) = delete;
        auto operator=(ScopedIterator const&) -> ScopedIterator const& = delete;
        auto operator=(ScopedIterator&&) -> ScopedIterator& = delete;

    private:
        BIT_MAP bitmap;
    };
}

#endif //OBJECT_ARRAY_DETAIL_SCOPEDITERATOR_H
