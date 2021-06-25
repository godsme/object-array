//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SIZEOFARRAY_H
#define OBJECT_ARRAY_SIZEOFARRAY_H

#include <cstddef>

template<typename T, std::size_t SIZE>
constexpr auto SizeOfArray(T (&)[SIZE]) -> auto {
    return SIZE;
}

constexpr auto SizeOfArray(std::nullptr_t) -> auto {
    return 0;
}

#endif //OBJECT_ARRAY_SIZEOFARRAY_H
