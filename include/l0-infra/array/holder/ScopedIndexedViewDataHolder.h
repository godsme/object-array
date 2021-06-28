//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_SCOPEDINDEXEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_SCOPEDINDEXEDVIEWDATAHOLDER_H

#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/holder/IndexedViewDataHolder.h>
#include <l0-infra/array/holder/detail/ScopedViewDataHolderInterface.h>

namespace holder {
    template<__cOnCePt(SimpleScopedRangedArrayLike) ARRAY, typename SUB_TYPE, bool IS_ORDERED>
    class ScopedIndexedViewDataHolder : public IndexedViewDataHolder<ARRAY, SUB_TYPE, IS_ORDERED> {
        using Parent = IndexedViewDataHolder<ARRAY, SUB_TYPE, IS_ORDERED>;
        using typename Parent::ArrayType;
        using Parent::This;
    public:
        using BitMap = typename ARRAY::BitMap;
        using Interface = detail::ScopedViewDataHolderInterface<ScopedIndexedViewDataHolder>;

    private:
        template<typename>
        friend class detail::ScopedViewDataHolderInterface;

        auto GetScope() const -> BitMap { return This()->GetArray().GetScope(); }
        auto GetScope() -> BitMap& { return This()->GetArray().GetScope(); }
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using RefScopedIndexedViewDataHolder = detail::RefViewDataHolder<ARRAY, ScopedIndexedViewDataHolder, ORDERED>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using ValueScopedIndexedViewDataHolder = detail::ValueViewDataHolder<ARRAY, ScopedIndexedViewDataHolder, ORDERED>;
}

#endif //OBJECT_ARRAY_SCOPEDINDEXEDVIEWDATAHOLDER_H
