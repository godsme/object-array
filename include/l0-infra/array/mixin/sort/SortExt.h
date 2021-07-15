//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_672E647CD58C4D4EAB283F5960DDEB3C
#define OBJECT_ARRAY_2_672E647CD58C4D4EAB283F5960DDEB3C

namespace mixin {
    template<typename T>
    struct SortExt : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        using T::Sort;
        using T::StableSort;
        using T::PartialSort;

        auto Sort() & -> decltype(auto) { return Sort(T::GetLess()); }
        auto Sort() && = delete;

        auto DescSort() & -> decltype(auto) { return Sort(T::GetGreater());}
        auto DescSort() && = delete;

        auto StableSort() & -> decltype(auto) { return StableSort(T::GetLess());}
        auto StableSort() && = delete;

        auto StableDescSort() & -> decltype(auto) { return StableSort(T::GetGreater());}
        auto StableDescSort() && = delete;

        auto PartialSort(SizeType n) & -> auto { return PartialSort(T::GetLess(), n); }
        auto PartialSort(SizeType n) && = delete;

        auto PartialDescSort(SizeType n) & -> auto { return PartialSort(T::GetGreater(), n); }
        auto PartialDescSort(SizeType n) && = delete;
    };
}

#endif //OBJECT_ARRAY_2_672E647CD58C4D4EAB283F5960DDEB3C
