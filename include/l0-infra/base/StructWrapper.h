//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_STRUCTWRAPPER_H
#define OBJECT_ARRAY_STRUCTWRAPPER_H

template<typename T, typename WRAPPER>
struct StructWrapper : protected T {
    static auto from(T const& raw) -> decltype(auto) {
        return (reinterpret_cast<WRAPPER const&>(raw));
    }

    static auto from(T& raw) -> decltype(auto) {
        return (reinterpret_cast<WRAPPER&>(raw));
    }

    auto to_struct() const -> T const& {
        return *this;
    }

    auto to_mutable_struct() -> T& {
        return *this;
    }

    auto operator*() const -> T const& {
        return *this;
    }

    auto operator*() -> T& {
        return *this;
    }

    operator T const&() const {
        return *this;
    }
};

#define DEF_STRUCT_WRAPPER(wrapper, raw_struct) \
struct wrapper : StructWrapper<raw_struct, wrapper>

#endif //OBJECT_ARRAY_STRUCTWRAPPER_H
