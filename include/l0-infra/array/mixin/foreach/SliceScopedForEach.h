//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_96381044F47F4EB3B86C6476C7952D3A
#define OBJECT_ARRAY_2_96381044F47F4EB3B86C6476C7952D3A

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct SliceScopedForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    private:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto ScopeForEach(BitMap scope, OP &&op) const -> auto {
            return T::template Unsafe_ScopeForEach<TO_NON_CONST>(scope.Mask(T::IndexBegin(), T::IndexEnd()), std::forward<OP>(op));
        }

    public:
        template<__oP_cOnCePt(OP)>
        auto ScopeForEach(BitMap scope, OP &&op) const -> auto {
            return ScopeForEach<false>(scope, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto ScopeForEach(BitMap scope, OP &&op) -> auto {
            return ScopeForEach<true>(scope, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_96381044F47F4EB3B86C6476C7952D3A
