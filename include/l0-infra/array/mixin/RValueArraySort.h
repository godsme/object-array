//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_RVALUEARRAYSORT_H
#define OBJECT_ARRAY_RVALUEARRAYSORT_H

#include <l0-infra/array/mixin/ArraySort.h>
#include <l0-infra/array/mixin/detail/ValueRangedArray.h>

namespace mixin {
    template<__cOnCePt(RangedArrayLike) T>
    struct RValueArraySort : ArraySort<T> {
        using Self = ArraySort<T>;

        using typename T::RangedArrayLike;
        using typename T::DataHolder;
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename Self::Owner;

    private:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    public:
        using Self::PartialSort;
        using Self::Sort;
        using Self::StableSort;

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && -> Owner {
            std::move(*this).Self::Sort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && -> Owner {
            std::move(*this).Self::StableSort(std::forward<LESS>(less));
            return reinterpret_cast<Owner&>(*this);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> view::ValueOrderedView<Array> {
            return {reinterpret_cast<Array&&>(*this), Self::DoPartialSort(std::forward<LESS>(less), n)};
        }
    };
}

#endif //OBJECT_ARRAY_RVALUEARRAYSORT_H
