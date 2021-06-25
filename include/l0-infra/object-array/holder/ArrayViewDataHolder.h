//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYVIEWDATAHOLDER_H
#define OBJECT_ARRAY_ARRAYVIEWDATAHOLDER_H

#include <l0-infra/object-array/holder/detail/ViewElemTrait.h>
#include <l0-infra/object-array/holder/detail/ContinuousArrayDataHolderInterface.h>
#include <l0-infra/object-array/detail/ArrayScope.h>
#include <l0-infra/base/IntOpt.h>
#include <type_traits>
#include <cstring>
#include <algorithm>
#include <l0-infra/object-array/holder/detail/ObjectTrait.h>

namespace holder {
    template <typename OBJ, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = OBJ>
    struct ArrayViewDataHolder {
        static_assert(std::is_trivial_v<OBJ>);
        using ElemType = ELEM;
        using ObjectType = ELEM;
        using SizeType = std::remove_const_t<SIZE_TYPE>;
        constexpr static auto MAX_SIZE = MAX_NUM;
        using ViewTrait = detail::ViewElemTrait_T<OBJ, ELEM>;
        using Trait = detail::ObjectTrait<ElemType>;

    public:
        using Interface = detail::ContinuousArrayDataHolderInterface<ArrayViewDataHolder>;

        ArrayViewDataHolder(OBJ* array, SIZE_TYPE& n)
                : elems(&ViewTrait::ObjToElem(*array))
                , num(n)
        {
            if(num > MAX_NUM) num = MAX_NUM;
        }

        ArrayViewDataHolder(ArrayViewDataHolder const& rhs)
            : elems{rhs.elems}, num(rhs.num) {}

        auto CopyFrom(OBJ const* array, std::size_t n) -> void {
            num = std::min(n, MAX_SIZE);
            ::memcpy(elems, array, sizeof(ELEM) * num);
        }

        auto operator=(ArrayViewDataHolder const& rhs) -> ArrayViewDataHolder& {
            CopyFrom(rhs.elems, rhs.num);
            return *this;
        }

        auto Clear() {
            num = 0;
        }

        auto ClearFrom(SizeType n) {
            num = std::min(num, n);
        }

        static auto ConstElemToObject(ElemType const& elem) -> ObjectType const& { return elem; }
        static auto ElemToObject(ElemType& elem) -> ObjectType& { return elem; }

        ElemType* elems;
        SIZE_TYPE& num;
    };
}

#endif //OBJECT_ARRAY_ARRAYVIEWDATAHOLDER_H
