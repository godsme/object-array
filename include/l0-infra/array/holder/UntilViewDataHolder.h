//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_UNTILVIEWDATAHOLDER_H
#define OBJECT_ARRAY_UNTILVIEWDATAHOLDER_H

#include <l0-infra/array/holder/detail/RangedViewDataHolderBase.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool ORDERED>
    struct UntilViewDataHolder : detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE, ORDERED> {
        using Parent = detail::RangedViewDataHolderBase<ARRAY, SUB_TYPE, ORDERED>;
        using Interface = detail::RangedViewDataHolderInterface<UntilViewDataHolder>;
        using typename Parent::SizeType;
        using typename Parent::ObjectType;

    public:
        UntilViewDataHolder(SizeType end)
                : end_{end} {}

    private:
        template<typename>
        friend class detail::RangedViewDataHolderInterface;

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return end_; }

    private:
        SizeType end_;
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using RefUntilViewDataHolder = detail::RefViewDataHolder<ARRAY, UntilViewDataHolder, ORDERED>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using ValueUntilViewDataHolder = detail::ValueViewDataHolder<ARRAY, UntilViewDataHolder, ORDERED>;
}

#endif //OBJECT_ARRAY_UNTILVIEWDATAHOLDER_H
