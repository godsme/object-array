//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_0E86EDAED5F543B6BB5C848908BF39D6
#define OBJECT_ARRAY_2_0E86EDAED5F543B6BB5C848908BF39D6

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct SortViewSort : T {
        using Self = T;

    protected:
        using typename T::ThisType;
        using typename T::ObjectType;
        using typename T::SizeType;

        template<__lEsS_cOnCePt(LESS)>
        auto DoSort(LESS&& less) & -> void {
            Self::InitIndices();
            Self::Unsafe_RangeSort(0, Self::Num(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto DoPartialSort(LESS&& less, SizeType n) & -> void
        {
            Self::InitIndices();
            auto num = Self::Unsafe_RangePartialSort(0, Self::Num(), std::forward<LESS>(less), n);
            Self::GetIndices().ClearFrom(num);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SelectMin(LESS&& less) & -> void {
            auto index = Self::GetArray().MinElemIndex(std::forward<LESS>(less));
            if(index) {
                Self::GetIndices().Append(*index);
            }
        }

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) & -> ThisType& {
            DoSort(std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        [[nodiscard]] auto Sort(LESS&& less) && -> ThisType {
            return std::move(Sort(std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) & -> ThisType& {
            Self::InitIndices();
            Self::Unsafe_RangeStableSort(0, Self::Num(), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        [[nodiscard]] auto StableSort(LESS&& less) && -> ThisType {
            return StableSort(std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElems(LESS&& less, SizeType n) & -> ThisType& {
            Self::GetIndices().Clear();

            if(n == 1) {
                SelectMin(std::forward<LESS>(less));
            } else if (n > 0) {
                DoPartialSort(std::forward<LESS>(less), n);
            }

            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) & -> ThisType& {
            return MinElems(std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        [[nodiscard]] auto MinElems(LESS&& less, SizeType n) && -> ThisType {
            return MinElems(std::forward<LESS>(less), n);
        }

        auto MinElems(SizeType n) & -> ThisType& {
            return MinElems(T::GetLess(), n);
        }

        auto MaxElems(SizeType n) & -> ThisType& {
            return MinElems(T::GetGreater(), n);
        }

        [[nodiscard]] auto MinElems(SizeType n) && -> ThisType {
            return MinElems(T::GetLess(), n);
        }

        [[nodiscard]] auto MaxElems(SizeType n) && -> ThisType {
            return MinElems(T::GetGreater(), n);
        }
    };
}

#endif //OBJECT_ARRAY_2_0E86EDAED5F543B6BB5C848908BF39D6
