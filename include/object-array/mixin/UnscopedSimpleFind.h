//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_UNSCOPEDSIMPLEFIND_H
#define OBJECT_ARRAY_UNSCOPEDSIMPLEFIND_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Pred.h>
#include <object-array/detail/MixinDef.h>
#include <optional>
#include <algorithm>

namespace mixin {
    template<_concept::RangedArrayLike T>
    __DEF_Array_MIXIN(UnscopedSimpleFind) {
        using Mixin<T>::Self;
    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto FindIndex(PRED&& pred) const -> std::optional<SizeType> {
            if (Self()->IndexBegin() >= Self()->IndexEnd()) return std::nullopt;
            for (auto i = Self()->IndexBegin(); i < Self()->IndexEnd(); i++) {
                if constexpr(_concept::WithIndexPred<PRED, ObjectType, SizeType>) {
                    if (pred(Self()->GetObj(i), i)) return i;
                } else {
                    if (pred(Self()->GetObj(i))) return i;
                }
            }
            return std::nullopt;
        }

        template<_concept::Pred<ObjectType, SizeType> PRED>
        auto Find(PRED&& pred) const -> ObjectType const* {
            if constexpr(_concept::WithIndexPred<PRED, ObjectType, SizeType>) {
                auto index = FindIndex(std::forward<PRED>(pred));
                return index ? &Self()->GetObj(*index) : nullptr;
            } else {
                if (Self()->IndexBegin() >= Self()->IndexEnd()) return nullptr;
                auto* found = std::find_if(Self()->ObjectBegin(), Self()->ObjectEnd(), std::forward<PRED>(pred));
                return found == Self()->ObjectEnd() ? nullptr : found;
            }
        }
    };
}

#endif //OBJECT_ARRAY_UNSCOPEDSIMPLEFIND_H
