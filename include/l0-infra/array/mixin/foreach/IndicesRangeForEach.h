//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_3C821C4579FD4468A6DB82B4EEFFD33C
#define OBJECT_ARRAY_2_3C821C4579FD4468A6DB82B4EEFFD33C

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    class IndicesRangeForEach : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto RangeForEach(SizeType from, SizeType until, OP &&op) const -> auto {
            return Self::GetIndices().Unsafe_RangeForEach(from, until, Self::template GetIndicesOp<TO_NON_CONST>(std::forward<OP>(op)));
        }
    };
}

#endif //OBJECT_ARRAY_2_3C821C4579FD4468A6DB82B4EEFFD33C
