//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_RVALUESCOPEDSORT_H
#define OBJECT_ARRAY_RVALUESCOPEDSORT_H

#include <l0-infra/array/mixin/ScopedSort.h>
#include <l0-infra/array/mixin/detail/ValueScopedRangedArray.h>

namespace mixin {
    template<__cOnCePt(ScopedRangedArrayLike) T>
    struct RValueScopedSort : ScopedSort<T> {
        using Self = ScopedSort<T>;

        using typename T::ScopedRangedArrayLike;
        using typename T::DataHolder;
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::Owner;

    private:
        using Array = detail::ValueScopedRangedArray<DataHolder, ScopedRangedArrayLike>;

    public:
        using Self::PartialSort;
        using Self::Sort;
        using Self::StableSort;
        using Self::GetScope;

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
        auto PartialSort(LESS&& less, SizeType n) && -> view::OrderedValueScopedView<Array> {
            static_assert(std::is_reference_v<decltype(GetScope())>);
            GetScope().KeepLowestBits(Self::DoPartialSort(std::forward<LESS>(less), n));
            return {reinterpret_cast<Array&&>(*this)};
        }
    };
}

#endif //OBJECT_ARRAY_RVALUESCOPEDSORT_H
