//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>
#include <l0-infra/array/holder/detail/ScopedViewDataHolderInterface.h>
#include <l0-infra/base/BitSet.h>
#include <l0-infra/array/holder/detail/ViewDataHolder.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool ORDERED>
    struct ScopedViewDataHolder : detail::ViewDataHolder<ARRAY> {
        using Parent = detail::ViewDataHolder<ARRAY>;
        using typename Parent::ObjectType;
        using typename Parent::SizeType;
        constexpr static bool IS_ORDERED = ORDERED;
        using BitMap = typename ARRAY::BitMap;

        using Interface = detail::ScopedViewDataHolderInterface<ScopedViewDataHolder>;

    private:
        dEcL_tHiS(SUB_TYPE);
    public:
        ScopedViewDataHolder(BitMap const& scope) : scope{scope} {}

    private:
        template<typename>
        friend class detail::ScopedViewDataHolderInterface;

        auto IndexBegin() const -> SizeType { return This()->GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetArray().GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetArray().GetObj(n); }

        auto GetScope() const -> BitMap const& { return scope; }
        auto GetScope() -> BitMap& { return scope; }

    private:
        BitMap scope;
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using RefScopedViewDataHolder = detail::RefViewDataHolder<ARRAY, ScopedViewDataHolder, ORDERED>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using ValueScopedViewDataHolder = detail::ValueViewDataHolder<ARRAY, ScopedViewDataHolder, ORDERED>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
