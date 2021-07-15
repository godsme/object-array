//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_1DF52766AC564284900237D80EE66C79
#define OBJECT_ARRAY_2_1DF52766AC564284900237D80EE66C79

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct SimpleForEach : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto DoForEach(OP &&op) const -> auto {
            return T::template RangeForEach<TO_NON_CONST>(0, T::Num(), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_1DF52766AC564284900237D80EE66C79
