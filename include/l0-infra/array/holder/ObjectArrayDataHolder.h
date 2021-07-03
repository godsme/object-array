//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
#define OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H

#include <l0-infra/array/holder/detail/ContinuousArrayDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayHolderTrait.h>
#include <l0-infra/array/holder/ArrayDataHolder.h>
#include <l0-infra/base/DeduceSizeType.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED>
    struct ObjectArrayHolderBase : ArrayDataHolder<OBJ, MAX_NUM, ORDERED> {
        using Parent = ArrayDataHolder<OBJ, MAX_NUM, ORDERED>;
        using ObjectType = typename Parent::ObjectType;
        using SizeType = typename Parent::SizeType;
        using ElemType = typename Parent::ElemType;
        using Trait = typename Parent::Trait;
        constexpr static SizeType MAX_SIZE = MAX_NUM;
        using Interface = ContinuousArrayDataHolderInterface<ObjectArrayHolderBase>;

    protected:
        using Parent::elems;

    private:
        template<typename>
        friend
        class ContinuousArrayDataHolderInterface;

        template<typename>
        friend
        class ArrayDataHolderInterface;

    protected:
        auto ClearContent() -> void {
            Parent::ClearContent(num);
        }

        auto DoClear() -> void {
            ClearContent();
            num = 0;
        }

        auto MoveFrom(ObjectArrayHolderBase &&rhs) {
            ConstructFrom(rhs.elems, num);
            rhs.DoClear();
        }

        auto CopyFrom(OBJ const *array, std::size_t n) -> void {
            if constexpr(!std::is_trivially_destructible_v<ElemType>) {
                DoClear();
            }
            num = std::min(n, MAX_NUM);
            ConstructFrom(array);
        }

    protected:
        ObjectArrayHolderBase() {}

        ObjectArrayHolderBase(ObjectArrayHolderBase const &rhs)
            : Parent{rhs.elems, rhs.num}, num{rhs.num}
        {}

        ObjectArrayHolderBase(ObjectArrayHolderBase &&rhs)
            : Parent{rhs.elems, rhs.num}, num{rhs.num}
        {
            rhs.DoClear();
        }

        ObjectArrayHolderBase(std::initializer_list<OBJ> l)
                : Parent{l}, num(std::min(l.size(), MAX_NUM))
        {}

    protected:
        SizeType num{};
    };

    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED, bool = std::is_const_v<OBJ>>
    struct ObjectArrayHolder : ObjectArrayHolderBase<OBJ, MAX_NUM, ORDERED> {
        using Parent = ObjectArrayHolderBase<OBJ, MAX_NUM, ORDERED>;
        using Parent::Parent;

        ObjectArrayHolder(std::initializer_list<OBJ> l) : Parent{l} {}

        ObjectArrayHolder(ObjectArrayHolder const&) = default;
        ObjectArrayHolder(ObjectArrayHolder&&) = default;

        auto operator=(ObjectArrayHolder const &) -> ObjectArrayHolder & = delete;
        auto operator=(ObjectArrayHolder&&) -> ObjectArrayHolder & = delete;
    };

    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED>
    struct ObjectArrayHolder<OBJ, MAX_NUM, ORDERED, false> : ObjectArrayHolderBase<OBJ, MAX_NUM, ORDERED> {
        using Parent = ObjectArrayHolderBase<OBJ, MAX_NUM, ORDERED>;
        using Parent::Parent;

        ObjectArrayHolder(std::initializer_list<OBJ> l) : Parent{l} {}

        ObjectArrayHolder(ObjectArrayHolder const&) = default;
        ObjectArrayHolder(ObjectArrayHolder&&) = default;

        auto operator=(ObjectArrayHolder const &rhs) -> ObjectArrayHolder & {
            Parent::DoClear();
            Parent::num = rhs.num;
            ConstructFrom(rhs.elems, rhs.num);
            return *this;
        }

        auto operator=(ObjectArrayHolder&& rhs) -> ObjectArrayHolder & {
            Parent::DoClear();
            Parent::num = rhs.num;
            ConstructFrom(rhs.elems, rhs.num);
            rhs.DoClear();
            return *this;
        }
    };

    template<typename OBJ, std::size_t MAX_NUM>
    using UnOrderedObjectArrayHolder = ObjectArrayHolder<OBJ, MAX_NUM, false>;
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    using ObjectArrayDataHolder = detail::Holder<OBJ, MAX_NUM, detail::UnOrderedObjectArrayHolder>;
}

#endif //OBJECT_ARRAY_OBJECTARRAYDATAHOLDER_H
