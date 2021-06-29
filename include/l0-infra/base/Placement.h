//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_PLACEMENT_H
#define OBJECT_ARRAY_PLACEMENT_H

#include <l0-infra/base/detail/StorageTrait.h>
#include <utility>
#include <new>

template<typename T>
struct Placement {
    Placement() = default;

    template<typename ARG, typename ... ARGS>
    Placement(ARG&& arg, ARGS&& ... args) {
        if constexpr (std::is_aggregate_v<T>) {
            new (&storage) T{ std::forward<ARG>(arg), std::forward<ARGS>(args)... };
        } else {
            new (&storage) T( std::forward<ARG>(arg), std::forward<ARGS>(args)... );
        }
    }

    Placement(Placement&&) = default;
    Placement(Placement const&) = default;

    auto operator=(Placement const&) -> Placement& = default;
    auto operator=(Placement&&) -> Placement& = default;

    ~Placement() = default;

    template<typename ... ARGS>
    auto Emplace(ARGS&& ... args) -> T* {
        if constexpr(!(sizeof...(ARGS) == 0 && std::is_trivially_default_constructible_v<T>)) {
            if constexpr (std::is_aggregate_v<T>) {
                return new (&storage) T{ std::forward<ARGS>(args)... };
            } else {
                return new (&storage) T( std::forward<ARGS>(args)... );
            }
        } else {
            return GetObj();
        }
    }

    auto Destroy() -> void {
        if constexpr (!std::is_trivially_destructible_v<T>) {
            storage.object.~T();
        }
    }

    template<typename ... ARGS>
    auto Replace(ARGS&& ... args) -> T* {
        static_assert(!std::is_const_v<T>);
        Destroy();
        return Emplace(std::forward<ARGS>(args)...);
    }

    auto GetObj() const -> T const* {
        return &GetRef();
    }

    auto GetObj() -> T* {
        return &GetRef();
    }

    auto GetRef() const -> T const& {
        return storage.object;
    }

    auto GetRef() -> T& {
        return storage.object;
    }

    auto operator->() -> T* {
        return GetObj();
    }

    auto operator->() const -> T const* {
        return GetObj();
    }

    auto operator*() const -> T const& {
        return storage.object;
    }

    auto operator*() -> T& {
        return storage.object;
    }

private:
    typename detail::StorageTrait<T>::Type storage;
};

#endif //OBJECT_ARRAY_PLACEMENT_H
