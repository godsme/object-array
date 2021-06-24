//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_ARRAYELEMVISIT_H
#define OBJECT_ARRAY_ARRAYELEMVISIT_H

#include <object-array/concept/IndexedContainer.h>
#include <object-array/concept/Op.h>
#include <cub/base/InvokeConstMethod.h>

namespace mixin {
    template<_concept::IndexedContainer T>
    class ArrayElemVisit : public T {
        using Self = T;

    public:
        using SizeType = typename Self::SizeType;
        using ObjectType = typename Self::ObjectType;
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
        template<bool TO_NON_CONST, _concept::Op<ObjectType, SizeType> OP>
        auto Visit(OP &&op, SizeType i) const -> auto {
            if constexpr(_concept::WithIndexOp<OP, ObjectType, SizeType>) {
                return op(GetObject<TO_NON_CONST>(i), i);
            } else {
                return op(GetObject<TO_NON_CONST>(i));
            }
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYELEMVISIT_H
