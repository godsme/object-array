//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_C66AEF45D7FF473281DCBBB8CFE2A28E
#define OBJECT_ARRAY_2_C66AEF45D7FF473281DCBBB8CFE2A28E

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct UnsafeSliceScopedForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto Unsafe_ScopeForEach(BitMap scope, OP &&op) const -> auto {
            return T::template GetArray<TO_NON_CONST>().Unsafe_RangeScopeForEach(T::IndexBegin(), T::IndexEnd(), scope, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_C66AEF45D7FF473281DCBBB8CFE2A28E
