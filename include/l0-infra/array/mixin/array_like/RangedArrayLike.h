//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/mixin/detail/Mixins.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class RangedArrayLike : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

    public:
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
