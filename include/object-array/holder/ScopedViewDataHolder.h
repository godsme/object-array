//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/holder/detail/ArrayLikeViewDataHolder.h>
#include <cub/base/BitSet.h>

namespace holder::detail {
    template<typename T>
    class ScopedViewDataHolderConcept {
        dEcL_tHiS(T);
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType = typename T::SizeType;
        using BitMap = typename T::BitMap;
        using Maybe = typename T::Maybe;

        using ScopedRangedArrayLike = ScopedViewDataHolderConcept;

        auto GetObj(SizeType n) -> ObjectType& { return This()->GetObj(n); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto IndexBegin() const -> SizeType { return This()->IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->IndexEnd(); }
        auto GetScope() const -> BitMap { return This()->GetScope(); }
    };
}

namespace holder {
    template<_concept::SimpleRangedArrayLike ARRAY, typename SUB_TYPE>
    struct ScopedViewDataHolder {
        constexpr static auto IsConstArray = std::is_const_v<ARRAY>;
        using ArrayType = std::decay_t<ARRAY>;

        using ObjectType = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using ElemType   = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ElemType>, typename ArrayType::ElemType>;

        using BitMap = typename ArrayType::BitMap;
        using SizeType = typename ArrayType::SizeType;
        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;
        using Maybe = typename ArrayType::Maybe;

        using Concept = detail::ScopedViewDataHolderConcept<ScopedViewDataHolder>;

    private:
        dEcL_tHiS(SUB_TYPE);
    public:
        ScopedViewDataHolder(BitMap scope) : scope{scope} {}

        auto IndexBegin() const -> SizeType { return This()->GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetArray().GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetArray().GetObj(n); }

        auto GetScope() const -> BitMap { return scope; }

    private:
        BitMap scope;
    };

    template<_concept::SimpleRangedArrayLike ARRAY>
    using RefScopedViewDataHolder = detail::RefViewDataHolder<ARRAY, ScopedViewDataHolder>;

    template<_concept::SimpleRangedArrayLike ARRAY>
    using ValueScopedViewDataHolder = detail::ValueViewDataHolder<ARRAY, ScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
