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
        auto This() const -> T const* { return reinterpret_cast<T const*>(this); }
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType = typename T::SizeType;
        using BitMap = typename T::BitMap;

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto IndexBegin() const -> SizeType { return This()->IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->IndexEnd(); }
        auto GetScope() const -> BitMap { return This()->GetScope(); }
    };
}

namespace holder {
    template<_concept::SimpleRangedArrayLike ARRAY, typename SUB_TYPE>
    struct ScopedViewDataHolder {
        using ObjectType = typename ARRAY::ObjectType;
        using ElemType = typename ARRAY::ElemType;
        using BitMap = typename ARRAY::BitMap;
        using SizeType = typename ARRAY::SizeType;
        constexpr static SizeType MAX_SIZE = ARRAY::MAX_SIZE;

        using Concept = detail::ScopedViewDataHolderConcept<ScopedViewDataHolder>;

    private:
        constexpr static auto IsNonConstArray = !std::is_const_v<ARRAY>;
        auto This() const -> SUB_TYPE const* { return reinterpret_cast<SUB_TYPE const*>(this); }

    public:
        ScopedViewDataHolder(BitMap scope) : scope{scope} {}

        auto IndexBegin() const -> SizeType { return This()->GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetArray().GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& requires IsNonConstArray { return This()->GetArray().GetObj(n); }

        auto GetScope() const -> BitMap { return scope; }

    protected:
        BitMap scope;
    };

    template<_concept::SimpleRangedArrayLike ARRAY>
    using RefScopedViewDataHolder = detail::RefViewDataHolder<ARRAY, ScopedViewDataHolder>;

    template<_concept::SimpleRangedArrayLike ARRAY>
    using ValueScopedViewDataHolder = detail::ValueViewDataHolder<ARRAY, ScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
