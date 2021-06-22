//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_DEFMIXIN_H
#define OBJECT_ARRAY_DEFMIXIN_H

#include <type_traits>

namespace mixin {
    namespace detail {
        template<typename T, bool IS_PRIVATE, bool = std::is_empty_v<T>>
        struct Extends : protected T::Concept {};

        template<typename T>
        struct Extends<T, true, true> : protected T {};

        template<typename T>
        struct Extends<T, false, true> : T {};
    }
}

#define __Def_Mixin(Mixin, Concept) \
    template<Concept T, bool IS_PRIVATE = true, typename Self = detail::Extends<T, IS_PRIVATE>> \
    struct Mixin : Self

#endif //OBJECT_ARRAY_DEFMIXIN_H
