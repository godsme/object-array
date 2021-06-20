//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_INVOKECONSTMETHOD_H
#define OBJECT_ARRAY_INVOKECONSTMETHOD_H

#include <type_traits>
#include <concepts>

namespace detail {
    template<typename T> requires std::is_pointer_v<T>
    constexpr auto RemoveConst(T&& v) -> auto {
        return std::add_pointer_t<std::remove_const_t<std::remove_pointer_t<T>>>(v);
    }

    template<typename T> requires (!std::is_pointer_v<T> && std::is_const_v<T>)
    constexpr auto RemoveConst(T&& v) -> decltype(auto)  {
        return (std::remove_const_t<T>(v));
    }

    template<typename T> requires (!std::is_pointer_v<T> && !std::is_const_v<T>)
    constexpr auto RemoveConst(T&& v) -> decltype(auto) {
        return (v);
    }

    template<typename T> requires (!std::is_const_v<T>)
    constexpr auto ToConstThis(T* p) -> auto {
        return std::add_pointer_t<std::add_const_t<T>>(p);
    }
}

#define __INVOKE_CONST_METHOD(method) \
::detail::RemoveConst(::detail::ToConstThis(this)->method)

#endif //OBJECT_ARRAY_INVOKECONSTMETHOD_H
