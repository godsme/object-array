//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_ARRAYELEMVISIT_H
#define OBJECT_ARRAY_ARRAYELEMVISIT_H

#include <l0-infra/array/concept/IndexedContainer.h>
#include <l0-infra/array/concept/Op.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<__cOnCePt(IndexedContainer) T>
    class ArrayElemVisit : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;
        using Self::GetObj;

    protected:
        template<bool TO_NON_CONST>
        auto GetObject(SizeType n) const -> decltype(auto) {
            if constexpr(TO_NON_CONST) {
                return ::detail::RemoveConstThis(this)->GetObj(n);
            } else {
                return GetObj(n);
            }
        }
    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto Visit(OP &&op, SizeType i) const -> auto {
            if constexpr(__wItH_iNdEx_Op(OP)) {
                return op(GetObject<TO_NON_CONST>(i), i);
            } else {
                return op(GetObject<TO_NON_CONST>(i));
            }
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYELEMVISIT_H
