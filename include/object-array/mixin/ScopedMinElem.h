//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SCOPEDMINELEM_H
#define OBJECT_ARRAY_SCOPEDMINELEM_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/concept/Less.h>

namespace mixin {
    template<__cOnCePt(ConstRangedArrayLike) T>
    class ScopedMinElem : public T {
        using Self = T;
    public:
        using typename Self::Maybe;
        using typename Self::BitMap;
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        using Self::GetObj;

        using Self::IndexBegin;
        using Self::IndexEnd;

    public:
        template<bool SCOPE_CHECK, __lEsS_cOnCePt(LESS)>
        auto DoMinElemIndex(BitMap scope, LESS &&less) const -> Maybe {
            scope.template Align<SCOPE_CHECK>(IndexBegin(), IndexEnd());
            if(scope.none()) return std::nullopt;

            auto minElem = IndexBegin();
            const auto end = IndexEnd();
            for (; minElem < end; ++minElem) if (scope[minElem]) break;
            for (auto i = minElem+1; i < end; ++i) {
                if (scope[i] && less(GetObj(i), GetObj(minElem))) minElem = i;
            }
            return minElem;
        }

        template<bool SCOPE_CHECK, __lEsS_cOnCePt(LESS)>
        auto DoMinElem(BitMap scope, LESS &&less) const -> ObjectType const* {
            auto minElem = DoMinElemIndex<SCOPE_CHECK>(scope, std::forward<LESS>(less));
            return minElem ? &GetObj(*minElem) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDMINELEM_H
