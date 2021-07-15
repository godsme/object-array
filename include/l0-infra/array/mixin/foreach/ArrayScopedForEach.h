//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_F51BC8F1E0EF460DB656141E9ACCF2CD
#define OBJECT_ARRAY_2_F51BC8F1E0EF460DB656141E9ACCF2CD

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct ArrayScopedForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    protected:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto Unsafe_ScopeForEach(BitMap scope, OP &&op) const -> auto {
            return T::template Unsafe_RangeScopeForEach<TO_NON_CONST>(0, T::Num(), scope, std::forward<OP>(op));
        }

        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto ScopeForEach(BitMap scope, OP &&op) const -> auto {
            return Unsafe_ScopeForEach<TO_NON_CONST>(scope.Mask(0, T::Num()), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_F51BC8F1E0EF460DB656141E9ACCF2CD
