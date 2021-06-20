//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H

#include <object-array/detail/MixinDef.h>
#include <object-array/concept/RangedArrayLike.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    __DEF_Array_MIXIN(RangedArrayLike) {
        using Mixin<T>::Self;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        auto IndexBegin() const -> auto {
            return Self()->IndexBegin();
        }

        auto IndexEnd() const -> auto {
            return Self()->IndexEnd();
        }

        auto GetObj(SizeType n) const -> decltype(auto) {
            return Self()->GetObj(n);
        }

        auto ObjectBegin() const -> ObjectType const* {
            return &Self()->GetObj(Self()->IndexBegin());
        }

        auto ObjectEnd() const -> ObjectType const* {
            return &Self()->GetObj(Self()->IndexEnd());
        }
    };
}

#endif //OBJECT_ARRAY_MIXIN_RANGEDARRAYLIKE_H
