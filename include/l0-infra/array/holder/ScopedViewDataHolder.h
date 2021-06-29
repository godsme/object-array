//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>
#include <l0-infra/array/holder/detail/ScopedViewDataHolderInterface.h>
#include <l0-infra/base/BitSet.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool ORDERED>
    struct ScopedViewDataHolder {
        constexpr static auto IS_CONST = std::is_const_v<ARRAY> || ARRAY::CONST;
        using ArrayType = std::decay_t<ARRAY>;

        using ObjectType = std::conditional_t<IS_CONST, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;

        using SizeType = typename ArrayType::SizeType;
        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;
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
