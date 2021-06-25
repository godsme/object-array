//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_ARRAYSORT_H
#define OBJECT_ARRAY_ARRAYSORT_H

#include <l0-infra/array/concept/Less.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<typename T>
    struct ArraySort : T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

    private:
        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) -> SizeType {
            std::partial_sort(ObjectBegin(), ObjectBegin() + n, ObjectEnd(), std::forward<LESS>(less));
            return n;
        }

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) -> void {
            std::sort(ObjectBegin(), ObjectEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) -> void {
            std::stable_sort(ObjectBegin(), ObjectEnd(), std::forward<LESS>(less));
        }

        auto Sort() -> void {
            Sort(detail::DEFAULT_LESS_THAN);
        }

        auto DescSort() -> void {
            Sort(detail::DEFAULT_GREATER_THAN);
        }

        auto StableSort() -> void {
            StableSort(detail::DEFAULT_LESS_THAN);
        }

        auto StableDescSort() -> void {
            StableSort(detail::DEFAULT_GREATER_THAN);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) -> SizeType {
            if(n == 0) return 0;
            if(n < (IndexEnd() - IndexBegin())) {
                return DoPartialSort(std::forward<LESS>(less), n);
            } else {
                Sort(std::forward<LESS>(less));
                return IndexEnd() - IndexBegin();
            }
        }

        auto PartialSort(SizeType n) -> SizeType {
            return PartialSort(detail::DEFAULT_LESS_THAN, n);
        }

        auto PartialDescSort(SizeType n) -> SizeType {
            return PartialSort(detail::DEFAULT_GREATER_THAN, n);
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYSORT_H
