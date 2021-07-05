//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_SIMPLERANGEDCLEAR_H
#define OBJECT_ARRAY_SIMPLERANGEDCLEAR_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<typename T>
    class SimpleRangedClear : public T {
        using Self = T;

    public:
        using typename T::SizeType;

    public:
        auto ClearRange(SizeType from, SizeType until) -> void {
            for(auto i=from; i<until; i++) {
                Self::DoErase(from);
            }
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLERANGEDCLEAR_H
