//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDELEMCOUNT_H
#define OBJECT_ARRAY_SCOPEDELEMCOUNT_H

#include <object-array/concept/ScopedArrayLike.h>

namespace mixin {
    template<_concept::Scoped T>
    class ScopedElemCount : public T {
        using Self = T;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

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
    };
}

#endif //OBJECT_ARRAY_SCOPEDELEMCOUNT_H