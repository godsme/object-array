//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_RANGEDELEMSCOUNT_H
#define OBJECT_ARRAY_RANGEDELEMSCOUNT_H


#include <object-array/concept/RangedArrayLike.h>
#include <object-array/mixin/detail/Mixins.h>
#include <cub/base/InvokeConstMethod.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    class RangedElemCount : public T {
        using Self = T;

    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        using Self::IndexBegin;
        using Self::IndexEnd;

        auto GetNum() const -> SizeType {
            return IndexEnd() - IndexBegin();
        }

        auto Any() const -> bool {
            return IndexBegin() < IndexEnd();
        }

        auto None() const -> bool {
            return !Any();
        }

        auto Full() const -> bool {
            return IndexEnd() == Self::MAX_SIZE;
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDELEMSCOUNT_H
