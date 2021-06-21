//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_DEDUCEELEMTYPE_H
#define OBJECT_ARRAY_DEDUCEELEMTYPE_H

#include <cub/base/Placement.h>
#include <type_traits>


namespace holder::detail {
    template<typename OBJ>
    auto DeduceElemType() -> auto {
        if constexpr(std::is_trivially_default_constructible_v<OBJ>) {
            return OBJ{};
        } else {
            return Placement<OBJ>{};
        }
    }
}

namespace holder {
    template<typename OBJ>
    using ElemType = decltype(detail::DeduceElemType<OBJ>());
}

#endif //OBJECT_ARRAY_DEDUCEELEMTYPE_H
