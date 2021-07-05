//
// Created by Darwin Yuan on 2021/7/3.
//

#ifndef OBJECT_ARRAY_INDEXEDORDEREDRANGEDCLEAR_H
#define OBJECT_ARRAY_INDEXEDORDEREDRANGEDCLEAR_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<typename T>
    class IndexedOrderedRangedClear : public T {
        using Self = T;

    protected:
        using typename T::Trait;
        using typename T::ElemType;
        using typename T::SizeType;
        using typename T::OffsetType;

        using Self::GetIndices;
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::Num;

    private:
        auto ClearRange(SizeType from, SizeType until) -> void {
            for(auto i=from; i<until; i++) {
                auto index = GetIndices()[i];
                Self::Erase(index);
            }
            GetIndices().ClearRange(from, until);
        }

    public:
        auto Clear() -> void {
            ClearRange(IndexBegin(), IndexEnd());
        }

        auto ClearFrom(OffsetType from) -> void {
            ClearRange(from.ToIndex(Num()), Num());
        }

        auto Clear(OffsetType from, OffsetType until) -> void {
            ClearRange(from.ToIndex(Num()), until.ToIndex(Num()));
        }

        auto ClearUntil(OffsetType until) -> void {
            ClearRange(0, until.ToIndex(Num()));
        }
    };
}

#endif //OBJECT_ARRAY_INDEXEDORDEREDRANGEDCLEAR_H
