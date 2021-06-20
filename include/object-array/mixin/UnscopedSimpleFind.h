//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_UNSCOPEDSIMPLEFIND_H
#define OBJECT_ARRAY_UNSCOPEDSIMPLEFIND_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Pred.h>

namespace mixin {
    template<_concept::RangedArrayLike T>
    struct UnscopedSimpleFind {
    private:
        auto Self() const -> T const* {
            return reinterpret_cast<T const*>(this);
        }

        auto Self() -> T* {
            return reinterpret_cast<T*>(this);
        }
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
    };
}

#endif //OBJECT_ARRAY_UNSCOPEDSIMPLEFIND_H
