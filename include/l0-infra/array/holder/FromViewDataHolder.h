//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_FROMVIEWDATAHOLDER_H
#define OBJECT_ARRAY_FROMVIEWDATAHOLDER_H

#include <l0-infra/array/holder/detail/RangedViewDataHolderBase.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool IS_ORDERED>
    struct FromViewDataHolder : detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE, IS_ORDERED> {
        using Parent = detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE, IS_ORDERED>;
        using Interface = detail::RangedViewDataHolderInterface<FromViewDataHolder>;
        using typename Parent::SizeType;
        using typename Parent::ObjectType;
        using Parent::This;

    public:
        FromViewDataHolder(SizeType begin)
                : begin_{begin} {}

    private:
        template<typename>
        friend class detail::RangedViewDataHolderInterface;

        auto IndexBegin() const -> SizeType { return begin_; }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }

    protected:
        SizeType begin_;
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using RefFromViewDataHolder = detail::RefViewDataHolder<ARRAY, FromViewDataHolder, ORDERED>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using ValueFromViewDataHolder = detail::ValueViewDataHolder<ARRAY, FromViewDataHolder, ORDERED>;
}

#endif //OBJECT_ARRAY_FROMVIEWDATAHOLDER_H
