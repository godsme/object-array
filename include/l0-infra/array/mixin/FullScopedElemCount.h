//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H
#define OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H

#include <l0-infra/array/mixin/ScopedElemCount.h>

namespace mixin {
    template<__cOnCePt(Scoped) T>
    class FullScopedElemCount : public ScopedElemCount<T> {
        using Self = T;
    public:
        using typename Self::BitMap;

    public:
        using Self::GetScope;

        auto All() const -> bool {
            return GetScope().all();
        }

        auto GetAvailable() const -> BitMap {
            return ~GetScope();
        }
    };
}

#endif //OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H
