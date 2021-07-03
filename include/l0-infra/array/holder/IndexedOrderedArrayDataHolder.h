//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_INDEXEDORDEREDARRAYDATAHOLDER_H
#define OBJECT_ARRAY_INDEXEDORDEREDARRAYDATAHOLDER_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>

namespace holder::detail {
    template<typename DATA_HOLDER, typename COMPARE>
    struct IndexedOrderedArrayInterface : ContinuousArrayDataHolderInterface<DATA_HOLDER> {
        using typename ContinuousArrayDataHolderInterface<DATA_HOLDER>::ObjectType;
        constexpr static auto Compare = COMPARE{};
        auto Less(ObjectType const& lhs, ObjectType const& rhs) const -> bool {
            return Compare(lhs, rhs);
        }


    };

    template<typename OBJ, std::size_t MAX_SIZE, typename COMPARE>
    class IndexedOrderedArrayHolderBase : public ObjectArrayHolderBase<OBJ, MAX_SIZE, true> {
        using Parent = ObjectArrayHolder<OBJ, MAX_SIZE, true>;
        using typename Parent::SizeType;
    public:
        using Parent::Parent;

        IndexedOrderedArrayHolderBase() {}
        IndexedOrderedArrayHolderBase(IndexedOrderedArrayHolderBase const &rhs)
            : Parent{rhs}
        {
            ::memcpy(indices, rhs.indices, sizeof(SizeType) * rhs.num);
        }

        IndexedOrderedArrayHolderBase(IndexedOrderedArrayHolderBase &&rhs)
            : Parent{std::move(rhs)}
        {
            ::memcpy(indices, rhs.indices, sizeof(SizeType) * rhs.num);
            rhs.DoClear();
        }

    protected:
        ::detail::OrderedArrayIndices<MAX_SIZE> indices;
    };

    template<typename OBJ, std::size_t MAX_NUM, typename COMPARE, bool = std::is_const_v<OBJ>>
    struct IndexedOrderedArrayHolder : IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE> {
        using Parent = IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE>;
        using Parent::Parent;

        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder const&) = default;
        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder&&) = default;

        auto operator=(IndexedOrderedArrayHolder const &) -> ObjectArrayHolder & = delete;
        auto operator=(IndexedOrderedArrayHolder&&) -> ObjectArrayHolder & = delete;
    };

    template<typename OBJ, std::size_t MAX_NUM, typename COMPARE>
    struct IndexedOrderedArrayHolder<OBJ, MAX_NUM, COMPARE, false> : IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE> {
        using Parent = IndexedOrderedArrayHolderBase<OBJ, MAX_NUM, COMPARE>;
        using Parent::Parent;

        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder const&) = default;
        IndexedOrderedArrayHolder(IndexedOrderedArrayHolder&&) = default;

        auto operator=(IndexedOrderedArrayHolder const &rhs) -> IndexedOrderedArrayHolder & {
            Parent::DoClear();
            Parent::num = rhs.num;
            ConstructFrom(rhs.elems);
            ::memcpy(Parent::indices, rhs.indices, sizeof(SizeType) * rhs.num);
            return *this;
        }

        auto operator=(IndexedOrderedArrayHolder&& rhs) -> IndexedOrderedArrayHolder & {
            Parent::DoClear();
            Parent::num = rhs.num;
            ConstructFrom(rhs.elems);
            ::memcpy(Parent::indices, rhs.indices, sizeof(SizeType) * rhs.num);
            rhs.DoClear();
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
