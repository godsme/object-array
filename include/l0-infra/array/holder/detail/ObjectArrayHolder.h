//
// Created by Darwin Yuan on 2021/7/8.
//

#ifndef OBJECT_ARRAY_2_DETAIL_OBJECTARRAYHOLDER_H
#define OBJECT_ARRAY_2_DETAIL_OBJECTARRAYHOLDER_H

#include <l0-infra/array/holder/detail/ContiguousArrayHolder.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED, bool = std::is_const_v<OBJ>>
    struct ObjectArrayHolder : ContiguousArrayHolder<OBJ, MAX_NUM, ORDERED> {
        using Parent = ContiguousArrayHolder<OBJ, MAX_NUM, ORDERED>;
        using Parent::Parent;

        using ConstArrayHolder = ObjectArrayHolder<std::add_const_t<OBJ>, MAX_NUM, ORDERED>;
        using NonConstArrayHolder = ObjectArrayHolder<std::remove_const_t<OBJ>, MAX_NUM, ORDERED>;

        ObjectArrayHolder() {}

        ObjectArrayHolder(ConstArrayHolder const& rhs) : Parent{rhs} {}
        ObjectArrayHolder(ConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}
        ObjectArrayHolder(NonConstArrayHolder const& rhs) : Parent{rhs} {}
        ObjectArrayHolder(NonConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}

        auto operator=(ConstArrayHolder const &) -> ObjectArrayHolder & = delete;
        auto operator=(ConstArrayHolder&&) -> ObjectArrayHolder & = delete;
        auto operator=(NonConstArrayHolder const &) -> ObjectArrayHolder & = delete;
        auto operator=(NonConstArrayHolder&&) -> ObjectArrayHolder & = delete;
    };

    template<typename OBJ, std::size_t MAX_NUM, bool ORDERED>
    struct ObjectArrayHolder<OBJ, MAX_NUM, ORDERED, false> : ContiguousArrayHolder<OBJ, MAX_NUM, ORDERED> {
        using Parent = ContiguousArrayHolder<OBJ, MAX_NUM, ORDERED>;
        using Parent::Parent;

        using ConstArrayHolder = ObjectArrayHolder<std::add_const_t<OBJ>, MAX_NUM, ORDERED>;
        using NonConstArrayHolder = ObjectArrayHolder<std::remove_const_t<OBJ>, MAX_NUM, ORDERED>;

        ObjectArrayHolder() {}

        ObjectArrayHolder(ConstArrayHolder const& rhs) : Parent{rhs} {}
        ObjectArrayHolder(ConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}
        ObjectArrayHolder(NonConstArrayHolder const& rhs) : Parent{rhs} {}
        ObjectArrayHolder(NonConstArrayHolder&& rhs) : Parent{std::move(rhs)} {}

        auto operator=(ConstArrayHolder const &rhs) -> ObjectArrayHolder & {
            Parent::CopyAssignment(rhs);
            return *this;
        }

        auto operator=(ConstArrayHolder&& rhs) -> ObjectArrayHolder & {
            Parent::MoveAssignment(std::move(rhs));
            return *this;
        }

        auto operator=(NonConstArrayHolder const &rhs) -> ObjectArrayHolder & {
            Parent::CopyAssignment(rhs);
            return *this;
        }

        auto operator=(NonConstArrayHolder&& rhs) -> ObjectArrayHolder & {
            Parent::MoveAssignment(std::move(rhs));
            return *this;
        }
    };
}

#endif //OBJECT_ARRAY_2_DETAIL_OBJECTARRAYHOLDER_H
