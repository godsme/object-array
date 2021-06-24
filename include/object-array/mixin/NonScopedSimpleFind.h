//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_NONSCOPEDSIMPLEFIND_H
#define OBJECT_ARRAY_NONSCOPEDSIMPLEFIND_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Pred.h>
#include <optional>
#include <algorithm>

namespace mixin {
    template<_concept::ConstRangedArrayLike T>
    struct NonScopedSimpleFind : T {
        using Self = T;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using Maybe = typename T::Maybe;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

    public:
        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindIndex(PRED&& pred) const -> Maybe {
            if (IndexBegin() >= IndexEnd()) return std::nullopt;
            for (auto i = IndexBegin(); i < IndexEnd(); i++) {
                if constexpr(_concept::WithIndexPred<PRED, ObjectType, SizeType>) {
                    if (pred(GetObj(i), i)) return i;
                } else {
                    if (pred(GetObj(i))) return i;
                }
            }
            return std::nullopt;
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(PRED&& pred) const -> ObjectType const* {
            if constexpr(_concept::WithIndexPred<PRED, ObjectType, SizeType>) {
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
