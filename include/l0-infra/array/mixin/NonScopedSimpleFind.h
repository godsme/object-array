//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_NONSCOPEDSIMPLEFIND_H
#define OBJECT_ARRAY_NONSCOPEDSIMPLEFIND_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/concept/Pred.h>
#include <optional>
#include <algorithm>

namespace mixin {
    template<__cOnCePt(ConstRangedArrayLike) T>
    struct NonScopedSimpleFind : T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED&& pred) const -> Maybe {
            if (IndexBegin() >= IndexEnd()) return std::nullopt;
            for (auto i = IndexBegin(); i < IndexEnd(); i++) {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    if (pred(GetObj(i), i)) return i;
                } else {
                    if (pred(GetObj(i))) return i;
                }
            }
            return std::nullopt;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED&& pred) const -> ObjectType const* {
            if constexpr(__wItH_iNdEx_pReD(PRED)) {
                auto index = FindIndex(std::forward<PRED>(pred));
                return index ? &GetObj(*index) : nullptr;
            } else {
                if (IndexBegin() >= IndexEnd()) return nullptr;
                auto* found = std::find_if(ObjectBegin(), ObjectEnd(), std::forward<PRED>(pred));
                return found == ObjectEnd() ? nullptr : found;
            }
        }
    };
}

#endif //OBJECT_ARRAY_NONSCOPEDSIMPLEFIND_H