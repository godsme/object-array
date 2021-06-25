//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_RANGEDCLEAR_H
#define OBJECT_ARRAY_RANGEDCLEAR_H

#include <l0-infra/object-array/concept/ContinuousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ContinuousArrayLikeDataHolder) T>
    struct RangedClear : T {
        using typename T::Trait;
        using typename T::ElemType;
        using typename T::SizeType;
        using typename T::OffsetType;
        using typename T::EndOffsetType;

        using T::Elems;
        using T::Num;

    private:
        auto ClearContent(SizeType from, SizeType until) -> void {
            if constexpr (!std::is_trivially_destructible_v<ElemType>) {
                for(int i=from; i<until; i++) Trait::Destroy(Elems()[i]);
            }
        }

        auto CleanOrdered(SizeType from, SizeType until) {
            auto total = Num() - until;
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memmove(Elems() + from, Elems() + until, sizeof(ElemType) * total);
            } else {
                for(auto i=0; i<total; i++) {
                    Trait::Emplace(Elems()[from+i], std::move(Trait::ToObject(Elems()[until + i])));
                }
            }
        }

        auto Clean(SizeType from, SizeType until) {
            auto total = std::min(until - from, Num() - until);
            if constexpr (std::is_trivially_copyable_v<ElemType>) {
                ::memmove(Elems() + from, Elems() + Num() - total, sizeof(ElemType) * total);
            } else {
                auto moveFrom = Num() - total;
                for(auto i=0; i<total; i++) {
                    Trait::Emplace(Elems()[from+i], std::move(Trait::ToObject(Elems()[moveFrom + i])));
                }
            }
        }

        auto DoClearFrom(SizeType from) -> void {
            ClearContent(from, Num());
            Num() = std::min(from, Num());
        }

    public:
        template<bool ORDERED>
        auto ClearRange(SizeType from, SizeType until) -> void {
            if(from >= until || until >= Num()) return;
            ClearContent(from, until);
            if constexpr(ORDERED) {
                CleanOrdered(from, until);
            } else {
                Clean(from, until);
            }
            Num() -= (until - from);
        }

        auto ClearFrom(OffsetType from) -> void {
            DoClearFrom(from.ToIndex(Num()));
        }

        template<bool ORDERED>
        auto Clear(OffsetType from, EndOffsetType until) -> void {
            ClearRange<ORDERED>(from.ToIndex(Num()), until.ToIndex(Num()));
        }

        template<bool ORDERED>
        auto ClearUntil(EndOffsetType until) -> void {
            ClearRange<ORDERED>(0, until.ToIndex(Num()));
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDCLEAR_H
