//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_SCATTEREDARRAYHOLDER_H
#define OBJECT_ARRAY_2_SCATTEREDARRAYHOLDER_H

#include <l0-infra/array/holder/detail/ArrayHolder.h>
#include <l0-infra/array/holder/detail/Holder.h>
#include <l0-infra/array/detail/ArrayScope.h>
#include <l0-infra/array/mixin/array_like/ConstScatteredArrayLike.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <l0-infra/array/mixin/array_like/ScatteredArrayLike.h>

namespace holder::detail {
    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayDataHolder : ArrayHolder<OBJ, MAX_NUM> {
        using Parent = ArrayHolder<OBJ, MAX_NUM>;
        using typename Parent::ObjectType;
        using typename Parent::ElemType;
        using typename Parent::SizeType;
        using BitMap = ::detail::ArrayScope<MAX_NUM>;

        using ConstScatteredArrayHolder = ScatteredArrayDataHolder<std::add_const_t<OBJ>, MAX_NUM>;
        using NonConstScatteredArrayHolder = ScatteredArrayDataHolder<std::remove_const_t<OBJ>, MAX_NUM>;

    protected:
        using Parent::elems;

    private:
        template<typename OP>
        auto ForAll(OP &&op) -> void {
            auto bits = occupied;
            for (auto i = 0; bits.any(); i++, bits >>= 1) if (bits[0]) op(i);
        }

        auto Move(ScatteredArrayDataHolder &&rhs) {
            ForAll([&, this](auto i) {
                elems[i].Emplace(std::move(*rhs.elems[i]));
            });
            rhs.DoClear();
        }

        auto Copy(ScatteredArrayDataHolder const &rhs) -> void {
            ForAll([&, this](auto i) {
                elems[i].Emplace(*rhs.elems[i]);
            });
        }

        template<typename ... ARGS>
        auto DoEmplace(SizeType i, ARGS &&... args) -> auto * {
            occupied.set(i);
            return elems[i].Emplace(std::forward<ARGS>(args)...);
        }

    protected:
        auto ClearContent() -> void {
            if constexpr (!std::is_trivially_destructible_v<ElemType>) {
                ForAll([this](auto i) { elems[i].Destroy(); });
            }
        }

        auto CopyAssignment(ScatteredArrayDataHolder const &rhs) -> void {
            ClearContent();
            occupied = rhs.occupied;
            Copy(rhs);
        }

        auto MoveAssignment(ScatteredArrayDataHolder &&rhs) -> void {
            ClearContent();
            occupied = rhs.occupied;
            Move(std::move(rhs));
        }

        auto DoClear() -> void {
            ClearContent();
            occupied.reset();
        }

    public:
        ScatteredArrayDataHolder() {};

        ScatteredArrayDataHolder(std::initializer_list<OBJ> l)
            : Parent{l}, occupied(l.size(), BitMap::ENABLE) {
        }

        ScatteredArrayDataHolder(ConstScatteredArrayHolder const &rhs) : occupied{rhs.occupied} {
            Copy(rhs);
        }

        ScatteredArrayDataHolder(ConstScatteredArrayHolder &&rhs) : occupied{rhs.occupied} {
            Move(std::move(rhs));
        }

        ScatteredArrayDataHolder(NonConstScatteredArrayHolder const &rhs) : occupied{rhs.occupied} {
            Copy(rhs);
        }

        ScatteredArrayDataHolder(NonConstScatteredArrayHolder &&rhs) : occupied{rhs.occupied} {
            Move(std::move(rhs));
        }

    private:
        template<typename>
        friend class mixin::ConstScatteredArrayLike;

        template<typename>
        friend class mixin::ConstArrayLike;

        template<typename>
        friend class mixin::ScatteredArrayLike;

    protected:
        BitMap occupied;
    };

    template<typename OBJ, std::size_t MAX_NUM, bool = std::is_const_v<OBJ>>
    struct ScatteredArrayHolder : ScatteredArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ScatteredArrayDataHolder<OBJ, MAX_NUM>;
        using Parent::Parent;

        using ConstScatteredArrayHolder = ScatteredArrayHolder<std::add_const_t<OBJ>, MAX_NUM>;
        using NonConstScatteredArrayHolder = ScatteredArrayHolder<std::remove_const_t<OBJ>, MAX_NUM>;

        ScatteredArrayHolder() {}

        ScatteredArrayHolder(ConstScatteredArrayHolder const & rhs) : Parent{rhs} {}
        ScatteredArrayHolder(NonConstScatteredArrayHolder const & rhs) : Parent{rhs} {}
        ScatteredArrayHolder(ConstScatteredArrayHolder&& rhs) : Parent{std::move(rhs)} {}
        ScatteredArrayHolder(NonConstScatteredArrayHolder&& rhs) : Parent{std::move(rhs)} {}

        auto operator=(ConstScatteredArrayHolder const &) -> ScatteredArrayHolder & = delete;
        auto operator=(NonConstScatteredArrayHolder const&) -> ScatteredArrayHolder & = delete;
        auto operator=(ConstScatteredArrayHolder &&) -> ScatteredArrayHolder & = delete;
        auto operator=(NonConstScatteredArrayHolder&&) -> ScatteredArrayHolder & = delete;
    };

    template<typename OBJ, std::size_t MAX_NUM>
    struct ScatteredArrayHolder<OBJ, MAX_NUM, false> : ScatteredArrayDataHolder<OBJ, MAX_NUM> {
        using Parent = ScatteredArrayDataHolder<OBJ, MAX_NUM>;
        using Parent::Parent;

        using ConstScatteredArrayHolder = ScatteredArrayHolder<std::add_const_t<OBJ>, MAX_NUM>;
        using NonConstScatteredArrayHolder = ScatteredArrayHolder<std::remove_const_t<OBJ>, MAX_NUM>;

        ScatteredArrayHolder() {}

        ScatteredArrayHolder(ConstScatteredArrayHolder const & rhs) : Parent{rhs} {}
        ScatteredArrayHolder(NonConstScatteredArrayHolder const & rhs) : Parent{rhs} {}
        ScatteredArrayHolder(ConstScatteredArrayHolder&& rhs) : Parent{std::move(rhs)} {}
        ScatteredArrayHolder(NonConstScatteredArrayHolder&& rhs) : Parent{std::move(rhs)} {}

        auto operator=(ConstScatteredArrayHolder const &rhs) -> ScatteredArrayHolder & {
            Parent::CopyAssignment(rhs);
            return *this;
        }

        auto operator=(NonConstScatteredArrayHolder const &rhs) -> ScatteredArrayHolder & {
            Parent::CopyAssignment(rhs);
            return *this;
        }

        auto operator=(ConstScatteredArrayHolder&& rhs) -> ScatteredArrayHolder & {
            Parent::MoveAssignment(std::move(rhs));
            return *this;
        }

        auto operator=(NonConstScatteredArrayHolder&& rhs) -> ScatteredArrayHolder & {
            Parent::MoveAssignment(std::move(rhs));
            return *this;
        }
    };

    template<typename OBJ, std::size_t MAX_NUM>
    using ScatteredArrayHolderAdapter = ScatteredArrayHolder<OBJ, MAX_NUM>;
}

namespace holder {
    template<typename OBJ, std::size_t MAX_NUM>
    using ScatteredArrayHolder = holder::detail::Holder<OBJ, MAX_NUM, holder::detail::ScatteredArrayHolderAdapter>;
}

#endif //OBJECT_ARRAY_2_SCATTEREDARRAYHOLDER_H
