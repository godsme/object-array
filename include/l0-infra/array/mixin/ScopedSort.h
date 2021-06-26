//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_SCOPEDSORT_H
#define OBJECT_ARRAY_SCOPEDSORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/detail/ScopedArrayIndices.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<__cOnCePt(ScopedRangedArrayLike) T>
    struct ScopedSort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        using typename Self::Owner;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetScope;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) -> decltype(auto) {
            ::detail::ScopedArrayIndices indices{*this};
            std::sort(indices.begin(), indices.end(), std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) -> decltype(auto) {
            ::detail::ScopedArrayIndices indices{*this};
            std::stable_sort(indices.begin(), indices.end(), std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) -> SizeType {
            if(n == 0) return 0;
            ::detail::ScopedArrayIndices indices{*this};
            if(n < indices.GetNum()) {
                std::partial_sort(indices.begin(), indices.begin() + n, indices.end(), std::forward<LESS>(less));
                return n;
            } else {
                std::sort(indices.begin(), indices.end(), std::forward<LESS>(less));
                return indices.GetNum();
            }
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSORT_H
