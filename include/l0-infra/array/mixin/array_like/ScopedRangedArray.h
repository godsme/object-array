//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_SCOPEDRANGEDARRAY_H
#define OBJECT_ARRAY_SCOPEDRANGEDARRAY_H

#include <l0-infra/array/concept/ScopedArrayLike.h>

namespace mixin {
    template<__cOnCePt(SimpleScopedRangedArrayLike) T>
    struct ScopedRangedArray : T {
        using Self = T;

        using Self::GetScope;
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

        using ScopedRangedArrayLike = ScopedRangedArray;
    };
}

#endif //OBJECT_ARRAY_SCOPEDRANGEDARRAY_H
