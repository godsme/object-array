//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H

#include <l0-infra/array/holder/detail/RangedViewDataHolderBase.h>
#include <l0-infra/array/holder/detail/RangedViewDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool IS_ORDERED>
    struct RangedViewDataHolder : detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE, IS_ORDERED> {
        using Parent = detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE, IS_ORDERED>;
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

    template<bool ORDERED>
    struct RangedViewDataHolderTrait {
        template<typename ARRAY, typename SUB_TYPE>
        using Type = RangedViewDataHolder<ARRAY, SUB_TYPE, ORDERED>;
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED=ARRAY::ORDERED>
    using RefRangedViewDataHolder = detail::RefViewDataHolder<ARRAY, RangedViewDataHolderTrait<ORDERED>::template Type>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED=ARRAY::ORDERED>
    using ValueRangedViewDataHolder = detail::ValueViewDataHolder<ARRAY, RangedViewDataHolderTrait<ORDERED>::template Type>;
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
