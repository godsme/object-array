//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDELEMCOUNT_H
#define OBJECT_ARRAY_SCOPEDELEMCOUNT_H

#include <l0-infra/object-array/concept/ScopedArrayLike.h>

namespace mixin {
    template<__cOnCePt(Scoped) T>
    class ScopedElemCount : public T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;

        using Self::GetScope;

        auto GetNum() const -> SizeType {
            return GetScope().count();
        }

        auto Any() const -> bool {
            return GetScope().any();
        }

        auto None() const -> bool {
            return GetScope().none();
        }

        auto GetOccupied() const -> BitMap {
            return GetScope();
        }

        auto IsPresent(SizeType n) const -> bool {
            return GetScope().test(n);
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDELEMCOUNT_H
