//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_RANGEDSCOPEDELEMCOUNT_H
#define OBJECT_ARRAY_RANGEDSCOPEDELEMCOUNT_H

#include <object-array/mixin/ScopedElemCount.h>

namespace mixin {
    template<_concept::Scoped T>
    class RangedScopedElemCount : public ScopedElemCount<T> {
        using Self = T;
    public:
        using BitMap = typename T::BitMap;
        using Self::GetScope;
        using Self::IndexBegin;
        using Self::IndexEnd;

    private:
        auto GetMask() const -> BitMap {
            BitMap scope;
            scope.set();
            auto n = Self::MAX_SIZE - IndexEnd();
            return ((scope << n) >> (n + IndexBegin())) << IndexBegin();
        }
    public:
        auto All() const -> bool {
            return GetMask() == GetScope();
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDSCOPEDELEMCOUNT_H
