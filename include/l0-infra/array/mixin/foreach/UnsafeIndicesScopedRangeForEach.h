//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_4AD9ADF897694083A5F39DB3E0536D86
#define OBJECT_ARRAY_2_4AD9ADF897694083A5F39DB3E0536D86

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    class UnsafeIndicesScopedRangeForEach : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        using typename Self::BitMap;

    protected:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto Unsafe_RangeScopeForEach(SizeType from, SizeType until, BitMap scope, OP &&op) const -> auto {
            return Self::GetIndices().Unsafe_RangeScopeForEach(from, until, scope, Self::template GetIndicesOp<TO_NON_CONST>(std::forward<OP>(op)));
        }

    public:
        template<__oP_cOnCePt(OP)>
        auto Unsafe_RangeScopeForEach(SizeType from, SizeType until, BitMap scope, OP &&op) const -> auto {
            return Unsafe_RangeScopeForEach<false>(from, until, scope, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto Unsafe_RangeScopeForEach(SizeType from, SizeType until, BitMap scope, OP &&op) -> auto {
            return Unsafe_RangeScopeForEach<true>(from, until, scope, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_4AD9ADF897694083A5F39DB3E0536D86
