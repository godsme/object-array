//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_ARRAYDATAHOLDER_H
#define OBJECT_ARRAY_ARRAYDATAHOLDER_H

#include <l0-infra/array/holder/detail/DeduceElemType.h>
#include <l0-infra/array/holder/detail/ObjectTrait.h>
#include <l0-infra/array/detail/ArrayScope.h>
#include <l0-infra/base/DeduceSizeType.h>
#include <l0-infra/base/BitSet.h>
#include <l0-infra/base/IntOpt.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ArrayDataHolder {
        using ObjectType = OBJ;
        using ElemType = holder::ElemType<OBJ>;
        using SizeType = DeduceSizeType_t<MAX_NUM>;
        using Trait = detail::ObjectTrait<ElemType>;
        constexpr static SizeType MAX_SIZE = MAX_NUM;

        static auto ConstElemToObject(ElemType const& elem) -> ObjectType const& {
            return Trait::ToObject(elem);
        }

        static auto ElemToObject(ElemType& elem) -> ObjectType& {
            return Trait::ToObject(elem);
        }

        ElemType elems[MAX_SIZE];
    };
}

#endif //OBJECT_ARRAY_ARRAYDATAHOLDER_H
