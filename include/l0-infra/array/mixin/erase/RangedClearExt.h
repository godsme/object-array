//
// Created by Darwin Yuan on 2021/7/5.
//

#ifndef OBJECT_ARRAY_RANGEDCLEAREXT_H
#define OBJECT_ARRAY_RANGEDCLEAREXT_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/ContiguousArrayLikeDataHolder.h>

namespace mixin {
    template<typename T>
    class RangedClearExt : public T {
        using Self = T;

    protected:
        using typename T::OffsetType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::Num;

    public:
        auto Clear() -> void {
            Self::ClearRange(IndexBegin(), IndexEnd());
        }

        auto ClearFrom(OffsetType from) -> void {
            Self::ClearRange(from.ToIndex(Num()), Num());
        }

        auto Clear(OffsetType from, OffsetType until) -> void {
            Self::ClearRange(from.ToIndex(Num()), until.ToIndex(Num()));
        }

        auto ClearUntil(OffsetType until) -> void {
            Self::ClearRange(0, until.ToIndex(Num()));
        }
    };
}

#endif //OBJECT_ARRAY_RANGEDCLEAREXT_H
