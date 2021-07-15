//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_ARRAYELEMVISIT_7C578BE8989E4B86B2F1891AC1D7FA3B
#define OBJECT_ARRAY_2_ARRAYELEMVISIT_7C578BE8989E4B86B2F1891AC1D7FA3B

#include <l0-infra/array/concept/Op.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct ArrayElemVisit : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        using T::GetObject;

    protected:
        template<bool TO_NON_CONST>
        auto GetObj(SizeType n) const -> decltype(auto) {
            if constexpr(TO_NON_CONST) {
                return ::detail::RemoveConstThis(this)->GetObject(n);
            } else {
                return T::GetObject(n);
            }
        }

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto Visit(OP &&op, SizeType i) const -> auto {
            if constexpr(__wItH_iNdEx_Op(OP)) {
                return op(GetObj<TO_NON_CONST>(i), i);
            } else {
                return op(GetObj<TO_NON_CONST>(i));
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_ARRAYELEMVISIT_7C578BE8989E4B86B2F1891AC1D7FA3B
