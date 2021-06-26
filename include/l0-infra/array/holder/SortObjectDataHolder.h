//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H
#define OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H

#include <l0-infra/array/ArrayIndices.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>

namespace holder::detail {
    template<typename HOLDER>
    class SortObjectDataHolderInterface {
        dEcL_tHiS(HOLDER);
    public:
        constexpr static auto MAX_SIZE = HOLDER::MAX_SIZE;
        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        auto GetObj(SizeType n) -> ObjectType & {
            return This()->GetObj(n);
        }

        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetObj(n);
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

        auto GetObj(SizeType n) -> ObjectType & {
            return This()->GetArray()[indices[n]];
        }

        auto GetObj(SizeType n) const -> ObjectType const& {
            return This()->GetArray()[indices[n]];
        }

    private:

        template<typename>
        friend class detail::SortObjectDataHolderInterface;

    private:
        ArrayIndices<MAX_SIZE> indices;
    };

    template<typename ARRAY>
    using RefSortObjectHolder = detail::RefViewDataHolder<ARRAY, SortObjectDataHolder>;

    template<typename ARRAY>
    using ValueSortObjectHolder = detail::ValueViewDataHolder<ARRAY, SortObjectDataHolder>;
}

#endif //OBJECT_ARRAY_SORTOBJECTDATAHOLDER_H
