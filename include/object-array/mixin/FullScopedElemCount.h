//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H
#define OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H

#include <object-array/mixin/ScopedElemCount.h>

namespace mixin {
    template<_concept::Scoped T>
    class FullScopedElemCount : public ScopedElemCount<T> {
        using Self = T;
    public:
        using Self::GetScope;

        auto All() const -> bool {
            return GetScope().all();
        }
    };
}

#endif //OBJECT_ARRAY_FULLSCOPEDELEMCOUNT_H
