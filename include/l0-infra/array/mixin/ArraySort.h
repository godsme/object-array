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
        using typename Self::Owner;
        using typename T::RangedArrayLike;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::ObjectBegin;
        using Self::ObjectEnd;

    protected:
        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) & -> SizeType {
            if(n == 0) return 0;
            if(n < (IndexEnd() - IndexBegin())) {
                std::partial_sort(ObjectBegin(), ObjectBegin() + n, ObjectEnd(), std::forward<LESS>(less));
                return n;
            } else {
                Sort(std::forward<LESS>(less));
                return IndexEnd() - IndexBegin();
            }
        }

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && -> void {
            std::sort(ObjectBegin(), ObjectEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) & -> decltype(auto) {
            std::move(*this).Sort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && -> void {
            std::stable_sort(ObjectBegin(), ObjectEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) & -> decltype(auto) {
            std::move(*this).StableSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) & -> view::OrderedView<RangedArrayLike> {
            return {reinterpret_cast<RangedArrayLike&>(*this), DoPartialSort(std::forward<LESS>(less), n)};
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> void {
            DoPartialSort(std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_ARRAYSORT_H
