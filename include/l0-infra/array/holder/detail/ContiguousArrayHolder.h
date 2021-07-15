//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_CONTIGUOUSARRAYHOLDER_H
#define OBJECT_ARRAY_2_CONTIGUOUSARRAYHOLDER_H

#include <l0-infra/array/holder/detail/ArrayHolder.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayLike.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <l0-infra/array/mixin/array_like/ArrayLike.h>
#include <algorithm>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED>
    class ContiguousArrayHolder : public ArrayHolder<OBJ, MAX_NUM, ORDERED> {
        using Parent = ArrayHolder<OBJ, MAX_NUM, ORDERED>;

        using ConstContiguousArrayHolder = ContiguousArrayHolder<std::add_const_t<OBJ>, MAX_NUM, ORDERED>;
        using NonConstContiguousArrayHolder = ContiguousArrayHolder<std::remove_const_t<OBJ>, MAX_NUM, ORDERED>;

    public:
        using typename Parent::SizeType;
        using typename Parent::ElemType;

    private:
        using Parent::elems;
        friend ConstContiguousArrayHolder;
        friend NonConstContiguousArrayHolder;

    private:
        auto ConstructFrom(ElemType const* array) -> void {
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memcpy(elems, array, sizeof(ElemType) * num);
            } else {
                for (auto i = 0; i < num; i++) {
                    elems[i].Emplace(*array[i]);
                }
            }
        }

        auto ConstructFrom(ElemType * array) -> void {
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memcpy(elems, array, sizeof(ElemType) * num);
            } else {
                for (auto i = 0; i < num; i++) {
                    elems[i].Emplace(std::move(*array[i]));
                }
            }
        }

    protected:
        auto ClearContent() -> void {
            if constexpr (!std::is_trivially_destructible_v<ElemType>) {
                for (int i = 0; i < num; i++) elems[i].Destroy();
            }
        }

    private:
        auto DoClear() -> void {
            ClearContent();
            num = 0;
        }

        auto MoveFrom(ContiguousArrayHolder &&rhs) {
            ConstructFrom(rhs.elems, num);
            rhs.DoClear();
        }

        auto CopyFrom(ElemType const *array, std::size_t n) -> void {
            DoClear();
            num = std::min(n, MAX_NUM);
            ConstructFrom(array);
        }

    protected:
        template<typename T>
        auto CopyAssignment(T const& rhs) -> void {
            DoClear();
            num = rhs.num;
            ConstructFrom(rhs.elems);
        }

        template<typename T>
        auto MoveAssignment(T &&rhs) -> void {
            DoClear();
            num = rhs.num;
            ConstructFrom(rhs.elems);
            rhs.DoClear();
        }

    public:
        using Parent::Parent;

        // DO NOT CHANGE IT TO `=default`
        // it's for avoiding unnecessary zero-initialization.
        ContiguousArrayHolder() {}
        ContiguousArrayHolder(std::initializer_list<OBJ> l)
            : Parent{l}
            , num(std::min(MAX_NUM, l.size()))
        {}

        ContiguousArrayHolder(ConstContiguousArrayHolder const &rhs) : num{rhs.num} {
            ConstructFrom(rhs.elems);
        }

        ContiguousArrayHolder(NonConstContiguousArrayHolder const &rhs) : num{rhs.num} {
            ConstructFrom(rhs.elems);
        }

        ContiguousArrayHolder(ConstContiguousArrayHolder &&rhs) : num{rhs.num} {
            ConstructFrom(rhs.elems);
            rhs.DoClear();
        }

        ContiguousArrayHolder(NonConstContiguousArrayHolder &&rhs) : num{rhs.num} {
            ConstructFrom(rhs.elems);
            rhs.DoClear();
        }

    private:
        template<typename>
        friend class mixin::ContiguousArrayLike;

        template<typename>
        friend class mixin::ConstArrayLike;

        template<typename>
        friend class mixin::ArrayLike;

    protected:
        SizeType num{};
    };
}

#endif //OBJECT_ARRAY_2_CONTIGUOUSARRAYHOLDER_H
