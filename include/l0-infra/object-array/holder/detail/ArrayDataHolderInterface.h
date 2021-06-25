//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYDATAHOLDERINTERFACE_H
#define OBJECT_ARRAY_ARRAYDATAHOLDERINTERFACE_H

#include <l0-infra/object-array/detail/CrtpHelper.h>

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ArrayDataHolderInterface {
        dEcL_tHiS(DATA_HOLDER);
    public:
        using ElemType = typename DATA_HOLDER::ElemType;
        using ObjectType = typename DATA_HOLDER::ObjectType;

        auto Elems() const -> ElemType const* { return This()->elems; }
        auto Elems() -> ElemType* { return This()->elems; }

        static auto ConstElemToObject(ElemType const& elem) -> ObjectType const& {
            return DATA_HOLDER::ConstElemToObject(elem);
        }

        static auto ElemToObject(ElemType& elem) -> ObjectType& {
            return DATA_HOLDER::ElemToObject(elem);
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYDATAHOLDERINTERFACE_H
