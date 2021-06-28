//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H

#include <l0-infra/array/holder/detail/RangedViewDataHolderBase.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE>
    struct RangedViewDataHolder : detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE> {
        using Parent = detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE>;
        using Interface = detail::RangedViewDataHolderInterface<RangedViewDataHolder>;
        using typename Parent::SizeType;
        using typename Parent::ObjectType;
        using Parent::This;

    public:
        RangedViewDataHolder(SizeType begin, SizeType end)
            : begin_{begin}, end_{end} {}

    private:
        template<typename>
        friend class detail::RangedViewDataHolderInterface;

        auto IndexBegin() const -> SizeType { return begin_; }
        auto IndexEnd() const -> SizeType { return end_; }

    protected:
        SizeType begin_;
        SizeType end_;
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY>
    using RefRangedViewDataHolder = detail::RefViewDataHolder<ARRAY, RangedViewDataHolder>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY>
    using ValueRangedViewDataHolder = detail::ValueViewDataHolder<ARRAY, RangedViewDataHolder>;
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
