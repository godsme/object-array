//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_RANGEDSCOPEDELEMCOUNT_H
#define OBJECT_ARRAY_RANGEDSCOPEDELEMCOUNT_H

#include <l0-infra/array/mixin/ScopedElemCount.h>

namespace mixin {
    template<__cOnCePt(Scoped) T>
    class RangedScopedElemCount : public ScopedElemCount<T> {
        using Self = T;
    public:
        using typename T::BitMap;

        using Self::GetScope;
        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        auto All() const -> bool {
            return BitMap(IndexBegin(), IndexEnd()) == GetScope();
        }

        auto GetAvailable() const -> BitMap {
            return (~GetScope()).Mask(IndexBegin(), IndexEnd());
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDSCOPEDELEMCOUNT_H