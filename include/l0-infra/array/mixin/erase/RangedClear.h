//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_RANGEDCLEAR_H
#define OBJECT_ARRAY_RANGEDCLEAR_H

#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<__cOnCePt(ContiguousArrayLikeDataHolder) T>
    class RangedClear : public T {
        using Self = T;

    protected:
        using typename T::Trait;
        using typename T::ElemType;
        using typename T::SizeType;
        using typename T::OffsetType;

        using Self::IndexBegin;
        using Self::IndexEnd;

    protected:
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
        auto ClearRange(SizeType from, SizeType until) -> void {
            if(from >= until || until > Num()) return;
            ClearContent(from, until);
            if constexpr(Self::ORDERED) {
                CleanOrdered(from, until);
            } else {
                Clean(from, until);
            }
            Num() -= (until - from);
        }

        auto Clear() -> void {
            ClearRange(IndexBegin(), IndexEnd());
        }

        auto ClearFrom(OffsetType from) -> void {
            DoClearFrom(from.ToIndex(Num()));
        }

        auto Clear(OffsetType from, OffsetType until) -> void {
            ClearRange(from.ToIndex(Num()), until.ToIndex(Num()));
        }

        auto ClearUntil(OffsetType until) -> void {
            ClearRange(0, until.ToIndex(Num()));
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDCLEAR_H
