//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H

#include <object-array/concept/IndexedContainer.h>
#include <object-array/holder/detail/DeduceElemType.h>
#include <object-array/holder/detail/ObjectTrait.h>
#include <object-array/holder/detail/RangedViewDataHolderConcept.h>
#include <object-array/holder/detail/ArrayLikeViewDataHolder.h>
#include <cub/base/BitSet.h>

namespace holder {
    template<_concept::IndexedContainer ARRAY, typename SUB_TYPE>
    struct RangedViewDataHolder {
        constexpr static auto IsConstArray = std::is_const_v<ARRAY>;
        using ArrayType = std::decay_t<ARRAY>;

        using ObjectType = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using ElemType   = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ElemType>, typename ArrayType::ElemType>;
        using SizeType = typename ArrayType::SizeType;
        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;

        using Concept = detail::RangedViewDataHolderConcept<RangedViewDataHolder>;

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

    template<_concept::IndexedContainer ARRAY>
    using RefRangedViewDataHolder = detail::RefViewDataHolder<ARRAY, RangedViewDataHolder>;

    template<_concept::IndexedContainer ARRAY>
    using ValueRangedViewDataHolder = detail::ValueViewDataHolder<ARRAY, RangedViewDataHolder>;
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
