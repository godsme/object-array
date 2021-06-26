//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_INDEXEDVIEWDATAHOLDER_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/holder/detail/RangedViewDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename OWNER, typename SUB_TYPE>
    class IndexedViewDataHolder {
        dEcL_tHiS(SUB_TYPE);
        constexpr static auto IsConstArray = std::is_const_v<std::remove_reference_t<ARRAY>>;
        using ArrayType = std::decay_t<ARRAY>;
    public:
        using ObjectType = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using SizeType   = typename ArrayType::SizeType;
        using Owner = OWNER;

        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;

        using Interface = detail::RangedViewDataHolderInterface<IndexedViewDataHolder>;

        auto IndexBegin() const -> SizeType { return This()->GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetArray().GetObj(n);}
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetArray().GetObj(n);}
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename OWNER>
    using RefIndexedViewDataHolder = detail::RefViewDataHolder<ARRAY, OWNER, IndexedViewDataHolder>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename OWNER>
    using ValueIndexedViewDataHolder = detail::ValueViewDataHolder<ARRAY, OWNER, IndexedViewDataHolder>;
}

#endif //OBJECT_ARRAY_INDEXEDVIEWDATAHOLDER_H
