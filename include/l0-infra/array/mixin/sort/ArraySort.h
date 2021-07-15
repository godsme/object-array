//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_D8DD85B683CB43ADAF2966D7DDBF1C41
#define OBJECT_ARRAY_2_D8DD85B683CB43ADAF2966D7DDBF1C41

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ArraySort : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        template<__lEsS_cOnCePt(LESS)>
        auto DoSort(LESS&& less) -> void {
            T::Unsafe_RangeSort(0, T::Num(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoStableSort(LESS&& less) -> void {
            T::Unsafe_RangeStableSort(0, T::Num(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) -> SizeType {
            return T::Unsafe_RangePartialSort(0, T::Num(), std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_2_D8DD85B683CB43ADAF2966D7DDBF1C41
