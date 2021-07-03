//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_INDEXEDORDEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_INDEXEDORDEREDARRAYDATAHOLDER_H

#include <l0-infra/array/holder/ScatteredArrayDataHolder.h>
#include <l0-infra/array/detail/OrderedArrayIndices.h>

namespace holder::detail {
    template<typename DATA_HOLDER, typename COMPARE>
    class IndexedOrderedArrayHolderInterface : public ScatteredArrayDataHolderInterface<DATA_HOLDER> {
        using Parent = ArrayDataHolderInterface<DATA_HOLDER>;
        dEcL_tHiS(DATA_HOLDER);
    public:
        using ObjectType = typename DATA_HOLDER::ObjectType;
        using SizeType = typename DATA_HOLDER::SizeType;
        using Compare  = COMPARE;
        using Trait = typename DATA_HOLDER::Trait;

        auto Num() const -> SizeType { return This()->indices.GetNum(); }
        auto GetIndices() -> decltype(auto) { return (This()->indices); }

        auto GetObj(SizeType n) -> ObjectType & {
            return Parent::ElemToObject(Parent::Elems()[This()->indices[n]]);
        }

        auto GetObj(SizeType n) const -> ObjectType const & {
            return Parent::ConstElemToObject(Parent::Elems()[This()->indices[n]]);
        }

        auto IndexBegin() const -> SizeType { return 0; }
        auto IndexEnd() const -> SizeType { return This()->indices.GetNum(); }
    };
}

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_SIZE, typename COMPARE>
    class IndexedOrderedArrayHolderBase : public ScatteredArrayDataHolder<OBJ, MAX_SIZE, true> {
        using Parent = ScatteredArrayDataHolder<OBJ, MAX_SIZE, true>;

    protected:
        auto DoClear() -> void {
            Parent::ClearContent();
        }
    public:
        using Interface = IndexedOrderedArrayHolderInterface<IndexedOrderedArrayHolderBase, COMPARE>;

    public:
        using Parent::Parent;

        IndexedOrderedArrayHolderBase() {}
        IndexedOrderedArrayHolderBase(IndexedOrderedArrayHolderBase const &rhs)
            : Parent{rhs}, indices{rhs.indices}
        {}

        IndexedOrderedArrayHolderBase(IndexedOrderedArrayHolderBase &&rhs)
            : Parent{std::move(rhs)}, indices{rhs.indices}
        {
            rhs.DoClear();
        }

    private:
        template<typename, typename >
        friend struct IndexedOrderedArrayHolderInterface;

        template<typename>
        friend struct ArrayDataHolderInterface;

    protected:
        ::detail::OrderedArrayIndices<MAX_SIZE> indices;
    };

    template<typename OBJ, std::size_t MAX_NUM, typename COMPARE, bool = std::is_const_v<OBJ>>
    struct IndexedOrderedArrayHolder : IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE> {
        using Parent = IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE>;
        using Parent::Parent;

        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder const&) = default;
        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder&&) = default;

        auto operator=(IndexedOrderedArrayHolder const &) -> IndexedOrderedArrayHolder & = delete;
        auto operator=(IndexedOrderedArrayHolder&&) -> IndexedOrderedArrayHolder & = delete;
    };

    template<typename OBJ, std::size_t MAX_NUM, typename COMPARE>
    struct IndexedOrderedArrayHolder<OBJ, MAX_NUM, COMPARE, false> : IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE> {
        using Parent = IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE>;
        using Parent::Parent;

        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder const&) = default;
        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder&&) = default;

        auto operator=(IndexedOrderedArrayHolder const &rhs) -> IndexedOrderedArrayHolder & {
            Parent::CopyFrom(rhs);
            Parent::indices = rhs.indices;
            return *this;
        }

        auto operator=(IndexedOrderedArrayHolder&& rhs) -> IndexedOrderedArrayHolder & {
            Parent::indices = rhs.indices;
            Parent::MoveFrom(std::move(rhs));
            return *this;
        }
    };

    template <typename COMPARE>
    struct IndexedOrderedArrayHolderAdapter {
        template<typename OBJ, std::size_t MAX_SIZE>
        using Type = IndexedOrderedArrayHolder<OBJ, MAX_SIZE, COMPARE>;
    };
}

namespace holder {
    template<typename OBJ, std::size_t MAX_SIZE, typename COMPARE>
    using IndexedOrderedArrayHolder = detail::Holder<OBJ, MAX_SIZE, detail::IndexedOrderedArrayHolderAdapter<COMPARE>::template Type>;
}

#endif //OBJECT_ARRAY_INDEXEDORDEREDARRAYDATAHOLDER_H
