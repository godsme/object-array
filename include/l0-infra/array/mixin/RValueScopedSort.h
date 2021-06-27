//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_RVALUESCOPEDSORT_H
#define OBJECT_ARRAY_RVALUESCOPEDSORT_H

#include <l0-infra/array/mixin/ScopedSort.h>
#include <l0-infra/array/mixin/detail/ValueRangedArray.h>

namespace mixin {
    template<__cOnCePt(ScopedRangedArrayLike) T>
    struct RValueScopedSort : ScopedSort<T> {
        using Self = ScopedSort<T>;

        using typename T::RangedArrayLike;
        using typename T::DataHolder;
        using typename T::ObjectType;
        using typename T::SizeType;

    private:
        using Array = detail::ValueRangedArray<DataHolder, RangedArrayLike>;

    public:
        using Self::PartialSort;
        using Self::GetScope;

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> view::OrderedValueScopedView<Array> {
            return {reinterpret_cast<Array&&>(*this), GetScope(), Self::DoPartialSort(std::forward<LESS>(less), n)};
        }
    };
}

#endif //OBJECT_ARRAY_RVALUESCOPEDSORT_H
