//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_ORDEREDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_ORDEREDVIEWDATAHOLDER_H

#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/detail/CrtpHelper.h>

namespace holder::detail {
    template<typename HOLDER>
    class OrderedViewDataHolderInterface {
        dEcL_tHiS(HOLDER);

    public:
        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        auto IndexBegin() const -> SizeType {
            return This()->IndexBegin();
        }

        auto IndexEnd() const -> SizeType {
            return This()->IndexEnd();
        }

        auto GetObj(SizeType n) const -> decltype(auto) {
            return This()->GetObj(n);
        }

        auto GetObj(SizeType n) -> decltype(auto) {
            return This()->GetObj(n);
        }
    };
}

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE>
    class OrderedViewDataHolder {
        dEcL_tHiS(SUB_TYPE);
        auto GetArray() const -> ARRAY const& { return This()->GetArray(); }
        auto GetArray() -> ARRAY& { return This()->GetArray(); }
    public:
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = typename ARRAY::ObjectType;
        constexpr static SizeType MAX_SIZE = ARRAY::MAX_SIZE;
        constexpr static bool IS_ORDERED = true;
        using Interface = detail::OrderedViewDataHolderInterface<OrderedViewDataHolder>;

    public:
        OrderedViewDataHolder(ARRAY& array, SizeType num)
            : indexEnd(array.IndexBegin() + num) {}

    private:
        template<typename>
        friend class detail::OrderedViewDataHolderInterface;

        auto IndexBegin() const -> SizeType { return GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return indexEnd; }
        auto GetObj(SizeType n) const -> ObjectType const& { return GetArray().GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& { return GetArray().GetObj(n); }

    private:
        SizeType indexEnd;
    };

    template<typename ARRAY>
    using RefOrdredViewHolder = detail::RefViewDataHolder<ARRAY, OrderedViewDataHolder>;

    template<typename ARRAY>
    using ValueOrderedViewHolder = detail::ValueViewDataHolder<ARRAY, OrderedViewDataHolder>;
}

#endif //OBJECT_ARRAY_ORDEREDVIEWDATAHOLDER_H
