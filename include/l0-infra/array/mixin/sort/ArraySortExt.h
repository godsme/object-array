//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_ALGO_ARRAYSORTEXT_H
#define OBJECT_ARRAY_ALGO_ARRAYSORTEXT_H

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/array/mixin/detail/DefaultLessThan.h>
#include <type_traits>
#include <algorithm>

namespace mixin {
    template<typename T>
    class ArraySortExt : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        using Self::DoPartialSort;
        using Self::Sort;
        using Self::PartialSort;
        using Self::StableSort;

        auto Sort() & -> decltype(auto) {
            return Sort(detail::DEFAULT_LESS_THAN);
        }

        auto Sort() && -> decltype(auto) {
            return std::move(*this).Sort(detail::DEFAULT_LESS_THAN);
        }

        auto DescSort() & -> decltype(auto) {
            return Sort(detail::DEFAULT_GREATER_THAN);
        }

        auto DescSort() && -> decltype(auto) {
            return std::move(*this).Sort(detail::DEFAULT_GREATER_THAN);
        }

        auto StableSort() & -> decltype(auto) {
            return StableSort(detail::DEFAULT_LESS_THAN);
        }

        auto StableSort() && -> decltype(auto) {
            return std::move(*this).StableSort(detail::DEFAULT_LESS_THAN);
        }

        auto StableDescSort() & -> decltype(auto) {
            return StableSort(detail::DEFAULT_GREATER_THAN);
        }

        auto StableDescSort() && -> decltype(auto) {
            return std::move(*this).StableSort(detail::DEFAULT_GREATER_THAN);
        }

        auto PartialSort(SizeType n) & -> auto {
            return PartialSort(detail::DEFAULT_LESS_THAN, n);
        }

        auto PartialSort(SizeType n) && -> auto {
            return std::move(*this).PartialSort(detail::DEFAULT_LESS_THAN, n);
        }

        auto PartialDescSort(SizeType n) & -> auto {
            return PartialSort(detail::DEFAULT_GREATER_THAN, n);
        }

        auto PartialDescSort(SizeType n) && -> auto {
            return std::move(*this).PartialSort(detail::DEFAULT_GREATER_THAN, n);
        }
    };
}

#endif //OBJECT_ARRAY_ALGO_ARRAYSORTEXT_H