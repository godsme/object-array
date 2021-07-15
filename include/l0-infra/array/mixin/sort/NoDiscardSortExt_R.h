//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_07215D04E2DA488CA5E02A7E186B916E
#define OBJECT_ARRAY_07215D04E2DA488CA5E02A7E186B916E

namespace mixin {
    template<typename T>
    struct NoDiscardSortExt_R : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        using T::Sort;
        using T::PartialSort;
        using T::StableSort;
        using T::DescSort;
        using T::StableDescSort;
        using T::PartialDescSort;

        [[nodiscard]] auto Sort() && -> auto { return std::move(*this).Sort(T::GetLess()); }
        [[nodiscard]] auto DescSort() && -> auto { return std::move(*this).Sort(T::GetGreater());}

        [[nodiscard]] auto StableSort() && -> auto { return std::move(*this).StableSort(T::GetLess());}
        [[nodiscard]] auto StableDescSort() && -> auto { return std::move(*this).StableSort(T::GetGreater());}

        [[nodiscard]] auto PartialSort(SizeType n) && -> auto { return std::move(*this).PartialSort(T::GetLess(), n); }
        [[nodiscard]] auto PartialDescSort(SizeType n) && -> auto { return std::move(*this).PartialSort(T::GetGreater(), n); }
    };
}

#endif //OBJECT_ARRAY_07215D04E2DA488CA5E02A7E186B916E
