//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_RANGEDELEMSCOUNT_H
#define OBJECT_ARRAY_RANGEDELEMSCOUNT_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class RangedElemCount : public T {
        using Self = T;

    protected:
        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

    public:
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
