//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_4F86D24997B24DD9A3A2E89D37C88E82
#define OBJECT_ARRAY_2_4F86D24997B24DD9A3A2E89D37C88E82

#include <l0-infra/array/OrderedObjectArray.h>
#include <l0-infra/array/IndexedOrderedArray.h>

namespace detail {
    template<typename T, std::size_t MAX_SIZE, typename COMPARE, bool = std::is_trivially_copyable_v<T> && (sizeof(T) <= sizeof(std::size_t))>
    struct OrderedArrayTrait {
        using Type = OrderedObjectArray<T, MAX_SIZE, COMPARE>;
    };

    template<typename T, std::size_t MAX_SIZE, typename COMPARE>
    struct OrderedArrayTrait<T, MAX_SIZE, COMPARE, false> {
        using Type = IndexedOrderedArray<T, MAX_SIZE, COMPARE>;
    };

    template<typename T, std::size_t MAX_SIZE, typename COMPARE>
    using OrderedArray = typename OrderedArrayTrait<T, MAX_SIZE, COMPARE>::Type;
}

template<typename T, std::size_t MAX_SIZE, typename COMPARE = std::less<T>>
using OrderedArray = detail::OrderedArray<T, MAX_SIZE, COMPARE>;

#endif //OBJECT_ARRAY_2_4F86D24997B24DD9A3A2E89D37C88E82
