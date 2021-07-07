//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYOFFSET_H
#define OBJECT_ARRAY_ARRAYOFFSET_H

#include <algorithm>

namespace detail {
    template<typename OFFSET_TYPE, typename SIZE_TYPE>
    struct ArrayOffset {
        constexpr ArrayOffset(OFFSET_TYPE offset) : offset{offset} {}

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
}

#endif //OBJECT_ARRAY_ARRAYOFFSET_H
