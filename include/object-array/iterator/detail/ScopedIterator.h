//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_DETAIL_SCOPEDITERATOR_H
#define OBJECT_ARRAY_DETAIL_SCOPEDITERATOR_H

#include <object-array/iterator/EmptyIterator.h>

namespace iterator::detail {
    template<typename BASE, typename BIT_MAP>
    class ScopedIterator : public BASE {
        auto init() {
            while(!bitmap[0] && bitmap.any()) { bitmap >>= 1; BASE::Forward(); }
            if(bitmap.none()) BASE::p = nullptr;
        }

    public:
        template<typename ... ARGS>
        ScopedIterator(BIT_MAP const& bitmap, ARGS&& ... args)
                : bitmap{bitmap}, BASE{std::forward(args)...} {}

        auto operator++() -> ScopedIterator& {
            do { bitmap >>= 1; BASE::Forward(); } while(!bitmap[0] && bitmap.any());
            if(bitmap.none()) BASE::p = nullptr;
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
