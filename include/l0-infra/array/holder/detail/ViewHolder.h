//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_VIEWHOLDER_72A5DB4C88734802B0D481401AA542AA
#define OBJECT_ARRAY_2_VIEWHOLDER_72A5DB4C88734802B0D481401AA542AA

#include <l0-infra/base/detail/CondConst.h>
#include <l0-infra/array/detail/CRTP.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include "ArrayLikeViewHolder.h"

namespace holder::detail {
    template<typename ARRAY, typename ARRAY_HOLDER>
    class ViewHolder {
        dEcL_tHiS(ARRAY_HOLDER);
    public:
        constexpr static auto IS_CONST = std::is_const_v<ARRAY> || ARRAY::IS_CONST;
        using ArrayType = std::decay_t<ARRAY>;
        using ObjectType = ::detail::CondConst_t<IS_CONST, typename ArrayType::ObjectType>;
        using SizeType = typename ArrayType::SizeType;
        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;
        constexpr static bool IS_ORDERED = ARRAY::IS_ORDERED;

    private:
        template<typename>
        friend class mixin::ViewedArray;

    protected:
        auto GetArray() const -> ARRAY const& {
            return This()->GetArray();
        }

        auto GetArray() -> ARRAY& {
            return This()->GetArray();
        }
    };
}

namespace holder {
    template<typename ARRAY>
    using View = detail::ArrayLikeViewHolder<ARRAY, detail::ViewHolder>;
}

#endif //OBJECT_ARRAY_2_VIEWHOLDER_72A5DB4C88734802B0D481401AA542AA
