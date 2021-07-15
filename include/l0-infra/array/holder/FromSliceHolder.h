//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_C59809C56FFA4FA58BB7E67396D1356C
#define OBJECT_ARRAY_2_C59809C56FFA4FA58BB7E67396D1356C

#include <l0-infra/array/holder/detail/ViewHolder.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewHolder.h>
#include <l0-infra/array/mixin/array_like/ConstRangeView.h>

namespace holder::detail {
    template<typename ARRAY, typename ARRAY_HOLDER>
    class FromSliceHolder : public ViewHolder<ARRAY, ARRAY_HOLDER> {
        using Parent = ViewHolder<ARRAY, ARRAY_HOLDER>;

    public:
        using typename Parent::SizeType;

        FromSliceHolder(SizeType from) : from{from} {}

    private:
        template<typename>
        friend class mixin::ConstRangeView;

    private:
        auto RangeBegin() const -> SizeType { return from; }
        auto RangeEnd() const   -> SizeType { return Parent::GetArray().IndexEnd(); }

    private:
        SizeType from;
    };
}

namespace holder {
    template<typename ARRAY>
    using FromSlice = detail::ArrayLikeViewHolder<ARRAY, detail::FromSliceHolder>;
}

#endif //OBJECT_ARRAY_2_C59809C56FFA4FA58BB7E67396D1356C
