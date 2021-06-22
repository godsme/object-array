//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDRANGEDARRAYLIKE_H
#define OBJECT_ARRAY_SCOPEDRANGEDARRAYLIKE_H

#include <object-array/concept/ScopedArrayLike.h>
#include <object-array/concept/Pred.h>
#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/mixin/RangedArrayLike.h>
#include <optional>
#include <algorithm>

namespace mixin {
    __Def_Mixin_Composite(ScopedRangedArrayLike, _concept::SimpleScopedRangedArrayLike, RangedArrayLike) {
        using Self::GetScope;
    };
}

#endif //OBJECT_ARRAY_SCOPEDRANGEDARRAYLIKE_H
