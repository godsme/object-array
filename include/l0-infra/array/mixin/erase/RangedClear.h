//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_3FF3685B0B854DA091B1D37B9BD712E4
#define OBJECT_ARRAY_2_3FF3685B0B854DA091B1D37B9BD712E4

#include <string>

namespace mixin {
    template<typename T>
    class RangedClear : public T {
        using Self = T;

    protected:
        using typename T::ElemType;

    public:
        using typename T::SizeType;
        using typename T::OffsetType;

    private:
        auto ClearContent(SizeType from, SizeType until) -> void {
            if constexpr (!std::is_trivially_destructible_v<typename T::ElemType>) {
                for(int i=from; i<until; i++) Self::Destroy(i);
            }
        }

        auto CleanOrdered(SizeType from, SizeType until) {
            auto total = Self::Num() - until;
            if constexpr (std::is_trivially_copyable_v < typename T::ElemType >) {
                auto *base = Self::Elems();
                ::memmove(base + from, base + until, sizeof(typename T::ElemType) * total);
            } else {
                for (auto i = 0; i < total; i++) {
                    T::MoveObject(from + i, until + i);
                }
            }
        }

        auto Clean(SizeType from, SizeType until) {
            auto num = Self::Num();
            auto total = std::min(until - from, num - until);
            if constexpr (std::is_trivially_copyable_v<typename T::ElemType>) {
                auto* base = Self::Elems();
                ::memmove(base + from, base + num - total, sizeof(typename T::ElemType) * total);
            } else {
                auto moveFrom = num - total;
                for(auto i=0; i<total; i++) {
                    Self::MoveObject(from + i, moveFrom + i);
                }
            }
        }

    protected:
        auto DoClearFrom(SizeType from) -> void {
            if(from < Self::Num()) {
                ClearContent(from, Self::Num());
                Self::Num() = from;
            }
        }

    public:
        auto Unsafe_Clear(SizeType from, SizeType until) -> void {
            if(from >= until) return;
            ClearContent(from, until);
            if constexpr(Self::IS_ORDERED) {
                CleanOrdered(from, until);
            } else {
                Clean(from, until);
            }
            Self::Num() -= (until - from);
        }

        auto Clear() -> void {
            ClearContent(0, Self::Num());
            Self::Num() = 0;
        }
    };
}

#endif //OBJECT_ARRAY_2_3FF3685B0B854DA091B1D37B9BD712E4
