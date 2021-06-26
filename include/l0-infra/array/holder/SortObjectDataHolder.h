//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H
#define OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H

#include <l0-infra/array/detail/ArrayIndices.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>

namespace holder::detail {

#define __sLiCe_SoRt_LaMbDa [&, &array = This()->GetArray()](auto l, auto r) { return less(array.GetObj(l), array.GetObj(r)); }

    template<typename HOLDER, typename OWNER>
    class SortObjectDataHolderInterface {
        dEcL_tHiS(HOLDER);
    public:
        constexpr static auto MAX_SIZE = HOLDER::MAX_SIZE;
        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) -> OWNER& {
            This()->indices.template Sort(__sLiCe_SoRt_LaMbDa);
            return reinterpret_cast<OWNER&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) -> OWNER& {
            This()->indices.template StableSort(__sLiCe_SoRt_LaMbDa);
            return reinterpret_cast<OWNER&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) -> SizeType {
            return This()->indices.template PartialSort(__sLiCe_SoRt_LaMbDa, n);
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
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename OWNER, typename SUB_TYPE>
    struct SortViewDataHolder {
        constexpr static auto MAX_SIZE = ARRAY::MAX_SIZE;
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = typename ARRAY::ObjectType;
        using Owner = OWNER;

        using Interface = detail::SortObjectDataHolderInterface<SortViewDataHolder, OWNER>;

    private:
        dEcL_tHiS(SUB_TYPE);

        auto GetArray() const -> ARRAY const& {
            return This()->GetArray();
        }

        auto GetArray() -> ARRAY& {
            return This()->GetArray();
        }

    private:

        template<typename, typename>
        friend class detail::SortObjectDataHolderInterface;

    public:
        ::detail::ArrayIndices<MAX_SIZE> indices;
    };

    template<typename ARRAY, typename OWNER>
    using RefSortViewHolder = detail::RefViewDataHolder<ARRAY, OWNER, SortViewDataHolder>;

    template<typename ARRAY, typename OWNER>
    using ValueSortViewHolder = detail::ValueViewDataHolder<ARRAY, OWNER, SortViewDataHolder>;
}

#endif //OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H
