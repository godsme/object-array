//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_INDEXEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_INDEXEDVIEWDATAHOLDER_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/holder/detail/RangedViewDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>
#include <l0-infra/array/holder/detail/ScopedViewDataHolderInterface.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE>
    class IndexedViewDataHolder {
    protected:
        dEcL_tHiS(SUB_TYPE);
        constexpr static auto IsConstArray = std::is_const_v<std::remove_reference_t<ARRAY>>;
        using ArrayType = std::decay_t<ARRAY>;
    public:
        using ObjectType = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using SizeType   = typename ArrayType::SizeType;

        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;
        constexpr static bool ORDERED = ArrayType::ORDERED;

        using Interface = detail::RangedViewDataHolderInterface<IndexedViewDataHolder>;

    private:
        template<typename>
        friend class detail::RangedViewDataHolderInterface;

        template<typename>
        friend class detail::ScopedViewDataHolderInterface;

        auto IndexBegin() const -> SizeType { return This()->GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetArray().GetObj(n);}
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetArray().GetObj(n);}
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY>
    using RefIndexedViewDataHolder = detail::RefViewDataHolder<ARRAY, IndexedViewDataHolder>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY>
    using ValueIndexedViewDataHolder = detail::ValueViewDataHolder<ARRAY, IndexedViewDataHolder>;
}

#endif //OBJECT_ARRAY_INDEXEDVIEWDATAHOLDER_H
