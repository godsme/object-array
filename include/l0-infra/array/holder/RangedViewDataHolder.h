//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H

#include <l0-infra/array/concept/IndexedContainer.h>
#include <l0-infra/array/holder/detail/DeduceElemType.h>
#include <l0-infra/array/holder/detail/ObjectTrait.h>
#include <l0-infra/array/holder/detail/RangedViewDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>
#include <l0-infra/base/BitSet.h>

namespace holder {
    template<__cOnCePt(IndexedContainer) ARRAY, typename OWNER, typename SUB_TYPE>
    struct RangedViewDataHolder {
        constexpr static auto IsConstArray = std::is_const_v<ARRAY>;
        using ArrayType = std::decay_t<ARRAY>;

        using ObjectType = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using ElemType   = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ElemType>, typename ArrayType::ElemType>;
        using SizeType   = typename ArrayType::SizeType;
        using Owner = OWNER;

        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;

        using Interface = detail::RangedViewDataHolderInterface<RangedViewDataHolder>;

    private:
        dEcL_tHiS(SUB_TYPE);
    public:
        RangedViewDataHolder(SizeType begin, SizeType end)
            : begin_{begin}, end_{end} {}

        auto IndexBegin() const -> SizeType { return begin_; }
        auto IndexEnd() const -> SizeType { return end_; }

        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetArray().GetObj(n);
        }

        auto GetObj(SizeType n) -> ObjectType& {
            return This()->GetArray().GetObj(n);
        }

    protected:
        SizeType begin_;
        SizeType end_;
    };

    template<__cOnCePt(IndexedContainer) ARRAY, typename OWNER>
    using RefRangedViewDataHolder = detail::RefViewDataHolder<ARRAY, OWNER, RangedViewDataHolder>;

    template<__cOnCePt(IndexedContainer) ARRAY, typename OWNER>
    using ValueRangedViewDataHolder = detail::ValueViewDataHolder<ARRAY, OWNER, RangedViewDataHolder>;
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H