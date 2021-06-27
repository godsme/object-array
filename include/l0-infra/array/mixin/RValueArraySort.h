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

    private:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    public:
        using Self::PartialSort;

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> view::ValueOrderedView<Array> {
            return {reinterpret_cast<Array&&>(*this), Self::DoPartialSort(std::forward<LESS>(less), n)};
        }
    };
}

#endif //OBJECT_ARRAY_RVALUEARRAYSORT_H
