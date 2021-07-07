//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H
#define OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H

#include <l0-infra/array/mixin/count/ScopedElemCount.h>

namespace mixin {
    template<__cOnCePt(Scoped) T>
    class FullScopedElemCount : public ScopedElemCount<T> {
        using Self = ScopedElemCount<T>;

    public:
        using typename Self::BitMap;
        using typename Self::SizeType;

    protected:
        using Self::GetScope;

    public:
        auto All() const -> bool {
            return GetScope().all();
        }

        auto NumOfFree() const -> SizeType {
            return Self::MAX_SIZE - Self::GetNum();
        }

        auto HasEnoughSlots(SizeType num) const -> bool {
            return num <= NumOfFree();
        }

        auto GetAvailable() const -> BitMap {
            return ~GetScope();
        }
    };
}

#endif //OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H
