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

        auto InitIndices() -> void {
            if constexpr(HOLDER::IS_SCOPED) {
                This()->indices.InitWithRange(This()->GetArray(), This()->GetArray().GetScope());
            } else {
                This()->indices.InitWithRange(This()->GetArray());
            }
        };

    public:
        constexpr static auto MAX_SIZE = HOLDER::MAX_SIZE;

        using SizeType = typename HOLDER::SizeType;
        using ObjectType = typename HOLDER::ObjectType;

        template<__lEsS_cOnCePt(LESS)>
        auto IndicesSort(LESS &&less) -> void {
            InitIndices();
            This()->indices.template Sort(__sLiCe_SoRt_LaMbDa);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto IndicesStableSort(LESS &&less) & -> void {
            InitIndices();
            This()->indices.template StableSort(__sLiCe_SoRt_LaMbDa);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto IndicesPartialSort(LESS &&less, SizeType n) -> SizeType {
            InitIndices();
            SizeType num = This()->indices.template DoPartialSort(__sLiCe_SoRt_LaMbDa, n);
            This()->indices.ClearFrom(num);
            return num;
        }

        auto GetObj(SizeType n) -> ObjectType & {
            return This()->GetArray().GetObj(This()->indices[n]);
        }

        auto GetObj(SizeType n) const -> ObjectType const & {
            return This()->GetArray().GetObj(This()->indices[n]);
        }

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return This()->indices.GetNum(); }

        auto GetIndices() -> decltype(auto) {
            return (This()->indices);
        }

        auto GetIndices() const -> decltype(auto) {
            return (This()->indices);
        }
    };
}

namespace holder::detail {
    template<typename T, typename = void>
    struct IsScopedArray : std::false_type{};

    template<typename T>
    struct IsScopedArray<T, std::enable_if_t<std::is_same_v<typename T::BitMap, decltype(std::declval<T const&>().GetScope())>>> : std::true_type{};
}

namespace holder {
    template<typename ARRAY, typename SUB_TYPE>
    struct SortViewDataHolder {
        constexpr static auto MAX_SIZE = ARRAY::MAX_SIZE;
        constexpr static bool IS_ORDERED = true;
        constexpr static bool IS_SCOPED = detail::IsScopedArray<ARRAY>::value;
        constexpr static bool IS_CONST = std::is_const_v<ARRAY> || ARRAY::IS_CONST;
        using SizeType = typename ARRAY::SizeType;
        using ObjectType = std::conditional_t<IS_CONST, std::add_const_t<typename ARRAY::ObjectType>, typename ARRAY::ObjectType>;

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
    using RefSortViewHolder = detail::RefViewDataHolder<ARRAY, SortViewDataHolder>;

    template<typename ARRAY>
    using ValueSortViewHolder = detail::ValueViewDataHolder<ARRAY, SortViewDataHolder>;
}

#endif //OBJECT_ARRAY_SORTVIEWDATAHOLDER_H
