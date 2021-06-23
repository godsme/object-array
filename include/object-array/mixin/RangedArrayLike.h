//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H

#include <object-array/mixin/detail/DefMixin.h>
#include <object-array/concept/RangedArrayLike.h>
#include <object-array/mixin/detail/Mixins.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    struct RangedArrayLike : detail::Extends<T> {
        using Self = detail::Extends<T>;

        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

        auto ObjectBegin() const -> ObjectType const* {
            return &GetObj(IndexBegin());
        }

        auto ObjectEnd() const -> ObjectType const* {
            return &GetObj(IndexEnd());
        }
    };
}

#endif //OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H
