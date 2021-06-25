//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SIMPLEMINELEM_H
#define OBJECT_ARRAY_SIMPLEMINELEM_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Less.h>
#include <algorithm>

namespace mixin {
    template<_concept::ConstRangedArrayLike T>
    class SimpleMinElem : public T {
        using Self = T;

    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;
        using typename Self::Maybe;

    public:
        using Self::IndexBegin;
        using Self::IndexEnd;

        using Self::GetObj;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

    public:
        template<_concept::Less<ObjectType> LESS>
        auto MinElemIndex(LESS &&less) const -> Maybe {
            if(IndexBegin() == IndexEnd()) return std::nullopt;
            auto min = IndexBegin();
            for(auto i = IndexBegin() + 1; i < IndexEnd(); ++i) {
                if(less(GetObj(i), GetObj(min))) min = i;
            }
            return min;
        }

        template<_concept::Less<ObjectType> LESS>
        auto MinElem(LESS &&less) const -> ObjectType const* {
            auto* found = std::min_element(ObjectBegin(), ObjectEnd(), std::forward<LESS>(less));
            return found == ObjectEnd() ? nullptr : found;
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMINELEM_H
