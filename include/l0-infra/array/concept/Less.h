//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_LESS_H
#define OBJECT_ARRAY_LESS_H

#include <l0-infra/array/config.h>
#if HAS_CONCEPT
#include <concepts>
#include <type_traits>

namespace _concept {
    template<typename LESS, typename ObjectType>
    concept Less = requires(LESS&& less, ObjectType const& lhs, ObjectType const& rhs) {
        { less(lhs, rhs) } -> std::same_as<bool>;
    };
}
#endif

#endif //OBJECT_ARRAY_LESS_H
