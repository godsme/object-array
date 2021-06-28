//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_ARRAYSCOPE_H
#define OBJECT_ARRAY_ARRAYSCOPE_H

#include <l0-infra/base/DeduceSizeType.h>
#include <l0-infra/base/BitSet.h>

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

        auto TestAndClear(SizeType n) -> bool {
            bool result = Parent::test(n);
            Parent::reset(n);
            return result;
        }

        auto GetLowestBits(SizeType n) -> ArrayScope {
            ArrayScope result{};
            if(n == 0) return result;
            auto num = 0;
            for(auto i=0; i<MAX_SIZE; i++) {
                if(Parent::test(i)) {
                    result.set(i);
                    if(++num == n) break;
                }
            }
            return result;
        }

        auto KeepLowestBits(SizeType n) -> ArrayScope& {
            *this = GetLowestBits(n);
            return *this;
        }
    };

}

#endif //OBJECT_ARRAY_ARRAYSCOPE_H
