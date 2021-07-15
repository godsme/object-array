//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_AEB081FB36F04BB08557B758053E170B
#define OBJECT_ARRAY_2_AEB081FB36F04BB08557B758053E170B


namespace mixin {
    template<typename T>
    struct BasicSort : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) & -> ThisType& {
            T::DoSort(std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Sort(LESS&& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) & -> ThisType& {
            T::DoStableSort(std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSort(LESS&& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) & -> auto {
            return T::MakeSlice(T::DoPartialSort(std::forward<LESS>(less), n));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSort(LESS&& less, SizeType n) && = delete;
    };
}

#endif //OBJECT_ARRAY_2_AEB081FB36F04BB08557B758053E170B
