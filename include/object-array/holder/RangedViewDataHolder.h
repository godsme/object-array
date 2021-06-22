//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H

#include <object-array/concept/IndexedContainer.h>
#include <object-array/holder/detail/DeduceElemType.h>
#include <object-array/holder/detail/ObjectTrait.h>
#include <cub/base/BitSet.h>

namespace holder::detail {
    template<typename T>
    class SliceDataHolderConcept {
        auto This() const -> T const* { return reinterpret_cast<T const*>(this); }
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType = typename T::SizeType;

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto IndexBegin() const -> SizeType { return This()->IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->IndexEnd(); }
    };
}

namespace holder {
    template<_concept::IndexedContainer ARRAY, typename SUB_TYPE>
    struct RangedViewDataHolder {
        using ObjectType = typename ARRAY::ObjectType;
        using ElemType = typename ARRAY::ElemType;
        //using BitMap = typename ARRAY::BitMap;
        using SizeType = typename ARRAY::SizeType;

        using Concept = detail::SliceDataHolderConcept<RangedViewDataHolder>;

    private:
        constexpr static auto IsNonConstArray = !std::is_const_v<ARRAY>;
        auto This() const -> SUB_TYPE const* { return reinterpret_cast<SUB_TYPE const*>(this); }

    public:
        RangedViewDataHolder(SizeType begin, SizeType end)
            : begin_{begin}, end_{end} {}

        auto IndexBegin() const -> SizeType { return begin_; }
        auto IndexEnd() const -> SizeType { return end_; }

        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetArray().GetObj(n);
        }

        auto GetObj(SizeType n) -> ObjectType& requires IsNonConstArray {
            return This()->GetArray().GetObj(n);
        }

    protected:
        SizeType begin_;
        SizeType end_;
    };

    template<_concept::IndexedContainer ARRAY>
    struct RefRangedViewDataHolder : RangedViewDataHolder<ARRAY, RefRangedViewDataHolder<ARRAY>> {
        using Parent = RangedViewDataHolder<ARRAY, RefRangedViewDataHolder<ARRAY>>;
        using SizeType = typename Parent::SizeType;

        RefRangedViewDataHolder(ARRAY& array, SizeType from, SizeType to)
            : array{array}, Parent{from, to} {}

        auto GetArray() const -> ARRAY& { return array; }

    protected:
        ARRAY& array;
    };

    template<_concept::IndexedContainer ARRAY>
    struct ValueRangedViewDataHolder : RangedViewDataHolder<ARRAY, ValueRangedViewDataHolder<ARRAY>> {
        using Parent = RangedViewDataHolder<ARRAY, ValueRangedViewDataHolder<ARRAY>>;
        using SizeType = typename Parent::SizeType;

        static_assert(std::is_move_constructible_v<ARRAY>);

    public:
        ValueRangedViewDataHolder(ARRAY&& array, SizeType from, SizeType to)
                : array{std::move(array)}, Parent{from, to} {}

        auto GetArray() const -> ARRAY const& { return array; }
        auto GetArray() -> ARRAY& { return array; }

    protected:
        ARRAY array;
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
