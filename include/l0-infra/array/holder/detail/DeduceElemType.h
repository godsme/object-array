//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_DEDUCEELEMTYPE_H
#define OBJECT_ARRAY_DEDUCEELEMTYPE_H

#include <l0-infra/base/Placement.h>
#include <type_traits>

namespace holder::detail {
    template<typename OBJ, bool = std::is_trivially_default_constructible_v<OBJ>>
    struct DeduceElemType {
        using Type = OBJ;
    };
    template<typename OBJ>
    struct DeduceElemType<OBJ, false> {
        using Type = Placement<OBJ>;
    };
}

namespace holder {
    template<typename OBJ>
    using ElemType = typename detail::DeduceElemType<OBJ>::Type;
}

#endif //OBJECT_ARRAY_DEDUCEELEMTYPE_H
