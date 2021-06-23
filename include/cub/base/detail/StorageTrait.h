//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_STORAGETRAIT_H
#define OBJECT_ARRAY_STORAGETRAIT_H

#include <type_traits>

namespace detail {
    template<typename T,
            bool = std::is_trivially_default_constructible_v<T>,
            bool = std::is_trivially_destructible_v<T>>
    struct StorageTrait {
        union Type {
            T object;
        };
    };

    template<typename T>
    struct StorageTrait<T, true, false> {
        union Type {
            ~Type() {}
            T object;
        };
    };

    template<typename T>
    struct StorageTrait<T, false, true> {
        union Type {
            Type() {}
            T object;
        };
    };

    template<typename T>
    struct StorageTrait<T, false, false> {
        union Type {
            Type() {}
            ~Type() {}
            Type(Type const&) = delete;
            T object;
        };
    };
}

#endif //OBJECT_ARRAY_STORAGETRAIT_H
