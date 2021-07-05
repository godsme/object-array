//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_SCOPEDFIND_H
#define OBJECT_ARRAY_SCOPEDFIND_H

#include <l0-infra/array/detail/ConceptDef.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/concept/Pred.h>
#include <l0-infra/base/IntOpt.h>
#include <optional>
#include <algorithm>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class ScopedFind : public T {
        using Self = T;
    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;
        using typename T::Maybe;

    protected:
        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto DoFindIndex(BitMap scope, PRED&& pred) const -> Maybe {
            if (IndexBegin() >= IndexEnd()) return std::nullopt;
            for (auto i = IndexBegin(); i < IndexEnd(); i++) {
                if(!scope[i]) continue;
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    if (pred(GetObj(i), i)) return i;
                } else {
                    if (pred(GetObj(i))) return i;
                }
            }
            return std::nullopt;
        }

        template<__pRed_CoNcEpT(PRED)>
        auto DoFind(BitMap scope, PRED&& pred) const -> ObjectType const* {
            auto index = DoFindIndex(scope, std::forward<PRED>(pred));
            return index ? &GetObj(*index) : nullptr;
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDFIND_H
