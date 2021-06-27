//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/mixin/detail/Mixins.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    struct RangedArrayLike : T {
        using Self = T;

        using typename T::SizeType;
        using typename T::ObjectType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

        auto ObjectBegin() const -> ObjectType const* {
            return &GetObj(IndexBegin());
        }

        auto ObjectBegin() -> ObjectType* {
            return &GetObj(IndexBegin());
        }

        auto ObjectEnd() const -> ObjectType const* {
            return &GetObj(IndexEnd());
        }

        auto ObjectEnd() -> ObjectType* {
            return &GetObj(IndexEnd());
        }
    };
}

#endif //OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H