//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_36CBB522055D470681E4C827483A7D6F
#define OBJECT_ARRAY_2_36CBB522055D470681E4C827483A7D6F

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    class ScatteredArrayForEach : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto DoForEach(OP &&op) const -> auto {
            return Self::template Unsafe_RangeScopeForEach<TO_NON_CONST>(0, T::MAX_SIZE, T::GetScope(), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_36CBB522055D470681E4C827483A7D6F
