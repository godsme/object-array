//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_SCATTEREDCLEAR_H
#define OBJECT_ARRAY_SCATTEREDCLEAR_H

#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<typename T>
    class ScatteredClear : public T {
        using Self = T;

    public:
        using Self::Clear;
    };
}

#endif //OBJECT_ARRAY_SCATTEREDCLEAR_H
