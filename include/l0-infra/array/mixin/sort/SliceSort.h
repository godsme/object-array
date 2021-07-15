//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_C2221561D23D4AB58DCE0D7B58F8375E
#define OBJECT_ARRAY_2_C2221561D23D4AB58DCE0D7B58F8375E

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct SliceSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;
        using typename T::ArrayType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto DoSort(LESS&& less) -> void {
            T::GetArray().Unsafe_RangeSort(T::IndexBegin(), T::IndexEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoStableSort(LESS&& less) -> void {
            T::GetArray().Unsafe_RangeStableSort(T::IndexBegin(), T::IndexEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) -> SizeType {
            return T::GetArray().Unsafe_RangePartialSort(T::IndexBegin(), T::IndexEnd(), std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_2_C2221561D23D4AB58DCE0D7B58F8375E
