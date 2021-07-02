//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_CONSTARRAYVIEWDATAHOLDER_H
#define OBJECT_ARRAY_CONSTARRAYVIEWDATAHOLDER_H

#include <l0-infra/array/holder/detail/ViewElemTrait.h>
#include <l0-infra/array/holder/detail/ContinuousArrayDataHolderInterface.h>
#include <l0-infra/array/detail/ArrayScope.h>
#include <l0-infra/array/holder/detail/ObjectTrait.h>
#include <l0-infra/base/IntOpt.h>
#include <type_traits>
#include <cstring>
#include <algorithm>

namespace holder {
    template <typename OBJ, std::size_t MAX_NUM, typename ELEM, bool ORDERED>
    struct ConstArrayViewDataHolder {
        using SizeType = DeduceSizeType_t<MAX_NUM>;
        using ElemType   = std::add_const_t<ELEM>;
        using ObjectType = std::add_const_t<ELEM>;
        constexpr static auto MAX_SIZE = MAX_NUM;
        constexpr static auto IS_ORDERED = ORDERED;
        constexpr static auto IS_CONST = true;
        using ViewTrait = detail::ViewElemTrait_T<std::decay_t<OBJ>, std::decay_t<ElemType>>;
        using Interface = detail::ContinuousArrayDataHolderInterface<ConstArrayViewDataHolder>;
        using Trait = detail::ObjectTrait<ElemType, ObjectType>;

    public:
        ConstArrayViewDataHolder(OBJ const* array, std::size_t n)
                : elems(&ViewTrait::ConstObjToElem(*array))
                , num(std::min(MAX_NUM, n))
        {}

    private:
        template<typename>
        friend class detail::ContinuousArrayDataHolderInterface;

        template<typename>
        friend class detail::ArrayDataHolderInterface;

    private:
        static auto ConstElemToObject(ElemType const& elem) -> ObjectType const& { return elem; }
        static auto ElemToObject(ElemType& elem) -> ObjectType& { return elem; }

        ElemType* elems;
        SizeType num;
    };
}

#endif //OBJECT_ARRAY_CONSTARRAYVIEWDATAHOLDER_H
