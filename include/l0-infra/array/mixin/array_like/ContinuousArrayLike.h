//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ConstWithNumber) T>
    class ContinuousArrayLike : public T {
        using Self = T;

    public:
        using typename T::SizeType;

    public:
        auto GetRange() const -> SizeType { return Self::Num(); }
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKE_H
