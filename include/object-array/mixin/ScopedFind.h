//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDFIND_H
#define OBJECT_ARRAY_SCOPEDFIND_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Pred.h>
#include <object-array/mixin/detail/DefMixin.h>
#include <optional>
#include <algorithm>

namespace mixin {
    template<_concept::RangedArrayLike T>
    struct ScopedFind : detail::Extends<T> {
        using Self = detail::Extends<T>;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;
        using BitMap = typename T::BitMap;

    private:
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

    public:
        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindIndex(BitMap scope, PRED&& pred) const -> std::optional<SizeType> {
            if (IndexBegin() >= IndexEnd()) return std::nullopt;
            for (auto i = IndexBegin(); i < IndexEnd(); i++) {
                if(!scope[i]) continue;
                if constexpr(_concept::WithIndexPred<PRED, ObjectType, SizeType>) {
                    if (pred(GetObj(i), i)) return i;
                } else {
                    if (pred(GetObj(i))) return i;
                }
            }
            return std::nullopt;
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(BitMap scope, PRED&& pred) const -> ObjectType const* {
            auto index = FindIndex(scope, std::forward<PRED>(pred));
            return index ? &GetObj(*index) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDFIND_H
