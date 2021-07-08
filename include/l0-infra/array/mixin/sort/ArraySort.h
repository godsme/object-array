//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_ARRAYSORT_H
#define OBJECT_ARRAY_ARRAYSORT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/view/OrderedView.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<__cOnCePt(RangedArrayLike) T>
    struct ArraySort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    protected:
        using Self::IndexBegin;
        using Self::IndexEnd;
        using typename Self::Owner;

    public:
        using Self::DoRangePartialSort;
        using Self::RangeSort;
        using Self::RangePartialSort;
        using Self::RangeStableSort;

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && -> void {
            RangeSort(IndexBegin(), IndexEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) & -> decltype(auto) {
            std::move(*this).Sort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && -> void {
            RangeStableSort(IndexBegin(), IndexBegin(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) & -> decltype(auto) {
            std::move(*this).StableSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) & -> SizeType {
            return DoRangePartialSort(IndexBegin(), IndexEnd(), std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) & -> auto {
            return RangePartialSort(IndexBegin(), IndexEnd(), std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> void {
            DoPartialSort(std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYSORT_H
