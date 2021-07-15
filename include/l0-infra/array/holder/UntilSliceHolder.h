//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_B5B310238D3F4971B0CAF93F5B3164E1
#define OBJECT_ARRAY_2_B5B310238D3F4971B0CAF93F5B3164E1

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewHolder.h>
#include <l0-infra/array/mixin/array_like/ConstRangeView.h>

namespace holder::detail {
    template<typename ARRAY, typename ARRAY_HOLDER>
    class UntilSliceHolder : public ViewHolder<ARRAY, ARRAY_HOLDER> {
        using Parent = ViewHolder<ARRAY, ARRAY_HOLDER>;

    public:
        using typename Parent::SizeType;

        UntilSliceHolder(SizeType until) : until{until} {}

    private:
        template<typename>
        friend class mixin::ConstRangeView;

    private:
        auto RangeBegin() const -> SizeType { return 0; }
        auto RangeEnd() const   -> SizeType { return until; }

    private:
        SizeType until;
    };
}

namespace holder {
    template<typename ARRAY>
    using UntilSlice = detail::ArrayLikeViewHolder<ARRAY, detail::UntilSliceHolder>;
}

#endif //OBJECT_ARRAY_2_B5B310238D3F4971B0CAF93F5B3164E1
