//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_ARRAYSCOPE_H
#define OBJECT_ARRAY_ARRAYSCOPE_H

#include <cub/base/DeduceSizeType.h>
#include <cub/base/BitSet.h>

namespace detail {
    template<std::size_t MAX_SIZE>
    class ArrayScope : public BitSet<MAX_SIZE> {
        using Parent = BitSet<MAX_SIZE>;
        using SizeType = DeduceSizeType_t<MAX_SIZE>;
    public:
        using Parent::Parent;
        ArrayScope(SizeType begin, SizeType end) {
            Parent::set();
            auto n = MAX_SIZE - end;
            (*this) = ((*this) << (n + begin)) >> n;
        }

        ArrayScope(Parent const& rhs) : Parent{rhs} {}
        auto operator=(ArrayScope const& rhs) -> ArrayScope& = default;
        auto operator=(Parent const& rhs) -> ArrayScope& {
            Parent::operator=(rhs);
            return *this;
        }

        auto operator<<=(SizeType n) -> ArrayScope& {
            Parent::operator<<=(n);
            return *this;
        }

        auto operator>>=(SizeType n) -> ArrayScope& {
            Parent::operator>>=(n);
            return *this;
        }

        constexpr auto operator~() const -> ArrayScope {
            return Parent::operator~();
        }

        auto AlignWithBegin(SizeType begin, SizeType end) -> ArrayScope& {
            auto n = MAX_SIZE - end;
            return (((*this) <<= n) >>= ( n + begin));
        }

        auto Mask(SizeType begin, SizeType end) -> ArrayScope& {
            return AlignWithBegin(begin, end) <<= begin;
        }

        template<bool MASK>
        auto Align(SizeType begin, SizeType end) -> ArrayScope& {
            if constexpr(MASK) {
                return AlignWithBegin(begin, end);
            } else {
                return (*this) >>= begin;
            }
        }
    };

}

#endif //OBJECT_ARRAY_ARRAYSCOPE_H
