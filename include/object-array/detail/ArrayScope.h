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

        auto Align(SizeType begin, SizeType end) const -> ArrayScope {
            auto n = MAX_SIZE - end;
            return (((*this) << n) >> ( n + begin)) << begin;
        }

        constexpr auto operator~() const -> ArrayScope {
            return Parent::operator~();
        }
    };

}

#endif //OBJECT_ARRAY_ARRAYSCOPE_H
