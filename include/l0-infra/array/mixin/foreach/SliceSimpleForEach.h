//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_A825DDEAF3C0459281A87F843E560886
#define OBJECT_ARRAY_2_A825DDEAF3C0459281A87F843E560886

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct SliceSimpleForEach : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto DoForEach(OP &&op) const -> auto {
            return T::template GetArray<TO_NON_CONST>().Unsafe_RangeForEach(T::IndexBegin(), T::IndexEnd(), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_A825DDEAF3C0459281A87F843E560886
