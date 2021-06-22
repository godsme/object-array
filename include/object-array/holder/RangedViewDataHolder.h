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
    template<_concept::IndexedContainer ARRAY>
    struct RangedViewDataHolder {
        using ObjectType = typename ARRAY::ObjectType;
        using ElemType = typename ARRAY::ElemType;
        using BitMap = typename ARRAY::BitMap;
        using SizeType = typename ARRAY::SizeType;

        using Concept = detail::SliceDataHolderConcept<RangedViewDataHolder>;

    private:
        constexpr static auto IsNonConstArray = !std::is_const_v<ARRAY>;

    public:
        RangedViewDataHolder(ARRAY& array, SizeType begin, SizeType end)
            : array{array}, begin_{begin}, end_{end} {}

        auto GetObj(SizeType n) const -> ObjectType const& {
            return array.GetObj(n);
        }

        auto GetObj(SizeType n) -> ObjectType& requires IsNonConstArray {
            return array.GetObj(n);
        }

        auto IndexBegin() const -> SizeType { return begin_; }
        auto IndexEnd() const -> SizeType { return end_; }

    protected:
        ARRAY& array;
        SizeType begin_;
        SizeType end_;
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDER_H
