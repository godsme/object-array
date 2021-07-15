//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_BB0C3309C6D04AC6A44B77A1B26A9139
#define OBJECT_ARRAY_2_BB0C3309C6D04AC6A44B77A1B26A9139


namespace mixin {
    template<typename T>
    struct BasicSort_R : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        using T::Sort;
        using T::PartialSort;
        using T::StableSort;

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && -> ThisType {
            T::DoSort(std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && -> ThisType {
            T::DoStableSort(std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && -> auto {
            return T::MakeSlice(T::DoPartialSort(std::forward<LESS>(less), n));
        }
    };
}

#endif //OBJECT_ARRAY_2_BB0C3309C6D04AC6A44B77A1B26A9139
