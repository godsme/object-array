//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H
#define OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H

#include <l0-infra/array/ArrayIndices.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>

namespace holder::detail {

#define __sLiCe_SoRt_LaMbDa [&, &array = This()->GetArray()](auto l, auto r) { return less(array[l], array[r]); }

    template<typename HOLDER>
    class SortObjectDataHolderInterface {
        dEcL_tHiS(HOLDER);
    public:
        constexpr static auto MAX_SIZE = HOLDER::MAX_SIZE;
        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) -> void {
            This()->indices.template Sort(__sLiCe_SoRt_LaMbDa);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) -> void {
            This()->indices.template StableSort(__sLiCe_SoRt_LaMbDa);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) -> SizeType {
            return This()->indices.template PartialSort(__sLiCe_SoRt_LaMbDa, n);
        }

        auto GetObj(SizeType n) -> ObjectType & {
            return This()->GetArray()[This()->indices[n]];
        }

        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetArray()[This()->indices[n]];
        }

        auto IndexBegin() const -> SizeType {
            return 0;
        }

        auto IndexEnd() const -> SizeType {
            return This()->indices.GetNum();
        }
    };
}

namespace holder {
    template<typename ARRAY, typename SUB_TYPE>
    struct SortObjectDataHolder {
        constexpr static auto MAX_SIZE = ARRAY::MAX_SIZE;
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = typename ARRAY::ObjectType;

        using Interface = detail::SortObjectDataHolderInterface<SortObjectDataHolder>;

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
        friend class detail::SortObjectDataHolderInterface;

    public:
        ArrayIndices<MAX_SIZE> indices;
    };

    template<typename ARRAY>
    using RefSortObjectHolder = detail::RefViewDataHolder<ARRAY, SortObjectDataHolder>;

    template<typename ARRAY>
    using ValueSortObjectHolder = detail::ValueViewDataHolder<ARRAY, SortObjectDataHolder>;
}

#endif //OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H
