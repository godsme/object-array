//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_SLICEHOLDER_338F530BE09D443DAC0DA86E15EAC96F
#define OBJECT_ARRAY_2_SLICEHOLDER_338F530BE09D443DAC0DA86E15EAC96F

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewHolder.h>
#include <l0-infra/array/mixin/array_like/ConstRangeView.h>

namespace holder::detail {
    template<typename ARRAY, typename ARRAY_HOLDER>
    class SliceHolder : public ViewHolder<ARRAY, ARRAY_HOLDER> {
        using Parent = ViewHolder<ARRAY, ARRAY_HOLDER>;

    public:
        using typename Parent::SizeType;

        SliceHolder(SizeType from, SizeType until) : from{from}, until{until} {}

    private:
        template<typename>
        friend class mixin::ConstRangeView;

    private:
        auto RangeBegin() const -> SizeType { return from; }
        auto RangeEnd() const   -> SizeType { return until; }

    private:
        SizeType from;
        SizeType until;
    };
}

namespace holder {
    template<typename ARRAY>
    using Slice = detail::ArrayLikeViewHolder<ARRAY, detail::SliceHolder>;
}

#endif //OBJECT_ARRAY_2_SLICEHOLDER_338F530BE09D443DAC0DA86E15EAC96F
