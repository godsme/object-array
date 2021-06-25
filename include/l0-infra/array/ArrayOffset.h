//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYOFFSET_H
#define OBJECT_ARRAY_ARRAYOFFSET_H

#include <algorithm>

template<typename OFFSET_TYPE, typename SIZE_TYPE>
struct ArrayOffset {
    constexpr ArrayOffset(OFFSET_TYPE offset): offset{offset} {}

    constexpr auto ToIndex(SIZE_TYPE size) const -> SIZE_TYPE {
        if (offset >= (OFFSET_TYPE) size) return size;
        if (offset >= 0) return offset;
        OFFSET_TYPE index = size + offset;
        return index < 0 ? 0 : index;
    }

    constexpr auto ToOffset(SIZE_TYPE size) const -> OFFSET_TYPE {
        if (offset >= (OFFSET_TYPE) size) return size;
        if (offset >= 0) return offset;
        OFFSET_TYPE index = size + offset;
        return index < 0 ? -1 : index;
    }

private:
    OFFSET_TYPE offset;
};

template<typename OFFSET_TYPE, typename SIZE_TYPE>
struct ArrayEndOffset {
    ArrayEndOffset(OFFSET_TYPE offset) : offset{offset} {}

    auto ToIndex(SIZE_TYPE size) const -> SIZE_TYPE {
        return std::min(size, SIZE_TYPE(offset.ToOffset(size) + 1));
    }
private:
    ArrayOffset<OFFSET_TYPE, SIZE_TYPE> offset;
};


#endif //OBJECT_ARRAY_ARRAYOFFSET_H
