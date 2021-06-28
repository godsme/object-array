//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTVIEWDATAHOLDER_H
#define OBJECT_ARRAY_SORTVIEWDATAHOLDER_H

#include <l0-infra/array/detail/ArrayIndices.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>

namespace holder::detail {

#define __sLiCe_SoRt_LaMbDa [&, &array = This()->GetArray()](auto l, auto r) { return less(array.GetObj(l), array.GetObj(r)); }

    template<typename HOLDER>
    class SortViewDataHolderInterface {
        dEcL_tHiS(HOLDER);
    public:
        constexpr static auto MAX_SIZE = HOLDER::MAX_SIZE;
        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        template<__lEsS_cOnCePt(LESS)>
        auto IndicesSort(LESS&& less) -> void {
            This()->indices.template Sort(__sLiCe_SoRt_LaMbDa);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto IndicesStableSort(LESS&& less) & -> void{
            This()->indices.template StableSort(__sLiCe_SoRt_LaMbDa);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto IndicesPartialSort(LESS&& less, SizeType n) -> SizeType {
            SizeType num = This()->indices.template DoPartialSort(__sLiCe_SoRt_LaMbDa, n);
            This()->indices.ClearFrom(num);
            return num;
        }

        auto GetObj(SizeType n) -> ObjectType & {
            return This()->GetArray().GetObj(This()->indices[n]);
        }

        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetArray().GetObj(This()->indices[n]);
        }

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return This()->indices.GetNum(); }
    };
}

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool ORDERED>
    struct SortViewDataHolder {
        constexpr static auto MAX_SIZE = ARRAY::MAX_SIZE;
        constexpr static bool IS_ORDERED = ORDERED;
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = typename ARRAY::ObjectType;

        using Interface = detail::SortViewDataHolderInterface<SortViewDataHolder>;

    private:
        dEcL_tHiS(SUB_TYPE);

        auto GetArray() const -> ARRAY const& {
            return This()->GetArray();
        }

        auto GetArray() -> ARRAY& {
            return This()->GetArray();
        }

    private:
        template<typename>
        friend class detail::SortViewDataHolderInterface;

    public:
        ::detail::ArrayIndices<MAX_SIZE> indices;
    };

    template<typename ARRAY>
    using RefSortViewHolder = detail::RefViewDataHolder<ARRAY, SortViewDataHolder, true>;

    template<typename ARRAY>
    using ValueSortViewHolder = detail::ValueViewDataHolder<ARRAY, SortViewDataHolder, true>;
}

#endif //OBJECT_ARRAY_SORTVIEWDATAHOLDER_H
