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
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

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

        auto All() const -> bool {
            return IndexEnd() == Self::MAX_SIZE;
        }

        auto GetOccupied() const -> BitMap {
            return BitMap(IndexBegin(), IndexEnd());
        }

        auto GetAvailable() const -> BitMap {
            return ~BitMap(IndexBegin(), IndexEnd());
        }

        auto IsPresent(SizeType n) const -> bool {
            return n >= IndexBegin() && n < IndexEnd();
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDELEMSCOUNT_H
