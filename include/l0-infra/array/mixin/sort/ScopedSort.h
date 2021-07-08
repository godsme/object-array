//
// Created by Darwin Yuan on 2021/6/27.
//

#ifndef OBJECT_ARRAY_SCOPEDSORT_H
#define OBJECT_ARRAY_SCOPEDSORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/concept/ScopedArrayLike.h>
#include <l0-infra/array/detail/ScopedArrayIndices.h>
#include <l0-infra/array/view/OrderedScopedView.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<typename T>
    class ScopedSort : public T {
        using Self = T;

    protected:
        using typename Self::Owner;
        using typename T::ScopedRangedArrayLike;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetScope;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;
        constexpr auto static MAX_SIZE = Self::MAX_SIZE;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) -> SizeType {
            if(n == 0) return 0;
            ::detail::ScopedArrayIndices indices{reinterpret_cast<ScopedRangedArrayLike&>(*this)};
            if(n < indices.GetNum()) {
                std::partial_sort(indices.begin(), indices.begin() + n, indices.end(), std::forward<LESS>(less));
                return n;
            } else {
                std::sort(indices.begin(), indices.end(), std::forward<LESS>(less));
                return indices.GetNum();
            }
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && -> void {
            ::detail::ScopedArrayIndices indices{reinterpret_cast<ScopedRangedArrayLike&>(*this)};
            std::sort(indices.begin(), indices.end(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) & -> decltype(auto) {
            std::move(*this).Sort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && -> void {
            ::detail::ScopedArrayIndices indices{reinterpret_cast<ScopedRangedArrayLike&>(*this)};
            std::stable_sort(indices.begin(), indices.end(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) & -> decltype(auto) {
            std::move(*this).StableSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) & -> view::OrderedScopedView<ScopedRangedArrayLike> {
            return {reinterpret_cast<ScopedRangedArrayLike&>(*this), DoPartialSort(std::forward<LESS>(less), n)};
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> SizeType {
            return DoPartialSort(std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSORT_H
