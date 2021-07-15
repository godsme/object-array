//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_002D418E2B944896AC84F5A5D9B97A0F
#define OBJECT_ARRAY_2_002D418E2B944896AC84F5A5D9B97A0F

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct ScopeSimpleForEach : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto DoForEach(OP &&op) const -> auto {
            return T::template GetArray<TO_NON_CONST>().Unsafe_ScopeForEach(T::GetScope(), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_002D418E2B944896AC84F5A5D9B97A0F
