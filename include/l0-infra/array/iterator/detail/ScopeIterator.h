//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_63B33BE0A31F4CDABFA0B0C9AF2BA392
#define OBJECT_ARRAY_2_63B33BE0A31F4CDABFA0B0C9AF2BA392

#include <l0-infra/array/iterator/EmptyIterator.h>

namespace iterator::detail {
    template<typename BASE, typename BIT_MAP>
    class ScopeIterator : public BASE {
        auto StepForward() -> void { bitmap >>= 1; BASE::StepForward(); }
        auto ForwardTo1stPresent() -> void {
            while(!bitmap[0] && bitmap.any()) StepForward();
        }

    public:
        template<typename ... ARGS>
        ScopeIterator(BIT_MAP const& bitmap, ARGS&& ... args)
                : bitmap{bitmap}, BASE{std::forward<ARGS>(args)...} {
            ForwardTo1stPresent();
        }

        auto operator++() -> ScopeIterator& {
            StepForward();
            ForwardTo1stPresent();
            return (*this);
        }

        auto operator!=(EmptyIterator const& rhs) const -> bool { return bitmap.any(); }

    public:
        ScopeIterator() = delete;
        ScopeIterator(ScopeIterator const&) = delete;
        ScopeIterator(ScopeIterator&&) = delete;
        auto operator=(ScopeIterator const&) -> ScopeIterator const& = delete;
        auto operator=(ScopeIterator&&) -> ScopeIterator& = delete;

    private:
        BIT_MAP bitmap;
    };
}

#endif //OBJECT_ARRAY_2_63B33BE0A31F4CDABFA0B0C9AF2BA392
