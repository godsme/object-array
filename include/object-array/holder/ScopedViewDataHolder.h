//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/holder/detail/ArrayLikeViewDataHolder.h>
#include <object-array/detail/CrtpHelper.h>
#include <cub/base/BitSet.h>

namespace holder::detail {
    template<typename T>
    class ScopedViewDataHolderInterface {
        dEcL_tHiS(T);
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType   = typename T::SizeType;
        using BitMap     = typename T::BitMap;

        constexpr static SizeType MAX_SIZE = T::MAX_SIZE;

        using ScopedRangedArrayLike = ScopedViewDataHolderInterface;

        auto GetObj(SizeType n) -> ObjectType& { return This()->GetObj(n); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto IndexBegin() const -> SizeType { return This()->IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->IndexEnd(); }
        auto GetScope() const -> BitMap { return This()->GetScope(); }
    };
}

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE>
    struct ScopedViewDataHolder {
        constexpr static auto IsConstArray = std::is_const_v<ARRAY>;
        using ArrayType = std::decay_t<ARRAY>;

        using ObjectType = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        //using ElemType   = std::conditional_t<IsConstArray, std::add_const_t<typename ArrayType::ElemType>, typename ArrayType::ElemType>;

        using SizeType = typename ArrayType::SizeType;
        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;
        using BitMap = typename ARRAY::BitMap;

        using Interface = detail::ScopedViewDataHolderInterface<ScopedViewDataHolder>;

    private:
        dEcL_tHiS(SUB_TYPE);
    public:
        ScopedViewDataHolder(BitMap const& scope) : scope{scope} {}

        auto IndexBegin() const -> SizeType { return This()->GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetArray().GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetArray().GetObj(n); }

        auto GetScope() const -> BitMap const& { return scope; }

    private:
        BitMap scope;
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY>
    using RefScopedViewDataHolder = detail::RefViewDataHolder<ARRAY, ScopedViewDataHolder>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY>
    using ValueScopedViewDataHolder = detail::ValueViewDataHolder<ARRAY, ScopedViewDataHolder>;
}

#endif //OBJECT_ARRAY_SCOPEDVIEWDATAHOLDER_H
