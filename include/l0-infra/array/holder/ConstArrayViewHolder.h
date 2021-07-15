//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_2E8817B33BAF4EFB98323F97CA7DB85F
#define OBJECT_ARRAY_2_2E8817B33BAF4EFB98323F97CA7DB85F

#include <l0-infra/array/holder/detail/ViewElemTrait.h>
#include <l0-infra/array/detail/ArrayScope.h>
#include <l0-infra/base/detail/DeduceIntOptional.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <l0-infra/base/IntOpt.h>
#include <type_traits>
#include <cstring>
#include <algorithm>

namespace holder {
    template <typename OBJ, std::size_t MAX_NUM, typename ELEM, bool ORDERED>
    struct ConstArrayViewHolder {
        using SizeType = ::detail::DeduceIntOptSizeType_t<MAX_NUM>;
        using ElemType   = std::add_const_t<ELEM>;
        using ObjectType = std::add_const_t<ELEM>;
        constexpr static auto MAX_SIZE = MAX_NUM;
        constexpr static auto IS_ORDERED = ORDERED;
        constexpr static auto IS_CONST = true;
        using ViewTrait = detail::ViewElemTrait_T<std::decay_t<OBJ>, std::decay_t<ElemType>>;

    private:
        using ElemArray = ElemType (&)[MAX_SIZE];

    public:
        ConstArrayViewHolder(OBJ const* array, std::size_t n)
                : elems(ElemArray(ViewTrait::ConstObjToElem(*array)))
                , num(std::min(MAX_SIZE, n))
        {}

    private:
        static auto ConstElemToObject(ElemType const& elem) -> ObjectType const& { return elem; }
        static auto ElemToObject(ElemType& elem) -> ObjectType& { return elem; }

        template<typename>
        friend class mixin::ConstArrayLike;

        template <typename>
        friend class mixin::ContiguousArrayLike;

    private:
        ElemArray elems;
        SizeType num;
    };
}

#endif //OBJECT_ARRAY_2_2E8817B33BAF4EFB98323F97CA7DB85F
