//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_ARRAYDATAHOLDER_H
#define OBJECT_ARRAY_ARRAYDATAHOLDER_H

#include <object-array/holder/detail/DeduceElemType.h>
#include <object-array/holder/detail/ObjectTrait.h>
#include <cub/base/BitSet.h>
#include <cub/base/IntOptional.h>

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ArrayDataHolder {
        using ObjectType = OBJ;
        using ElemType = holder::ElemType<OBJ>;
        using BitMap = BitSet<MAX_NUM>;
        using SizeType = DeduceSizeType_t<MAX_NUM>;
        using Trait = detail::ObjectTrait<ElemType>;
        //using Maybe = IntOptional<MAX_NUM>;
        constexpr static SizeType MAX_SIZE = MAX_NUM;

        static auto ElemToObject(ElemType const& elem) -> ObjectType const& {
            return Trait::ToObject(elem);
        }

        static auto ElemToObject(ElemType& elem) -> ObjectType& {
            return Trait::ToObject(elem);
        }

        auto Elems() const -> ElemType const* { return elems; }
        auto Elems() -> ElemType* { return elems; }

    protected:
        ElemType elems[MAX_SIZE];
    };
}

#endif //OBJECT_ARRAY_ARRAYDATAHOLDER_H
