//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_3B80E429AC824537B93A1B9748FD749F
#define OBJECT_ARRAY_2_3B80E429AC824537B93A1B9748FD749F

namespace mixin {
    template<typename T>
    struct SortExt_R : T {
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

        auto Sort() && -> auto { return std::move(*this).Sort(T::GetLess()); }
        auto DescSort() && -> auto { return std::move(*this).Sort(T::GetGreater());}

        auto StableSort() && -> auto { return std::move(*this).StableSort(T::GetLess());}
        auto StableDescSort() && -> auto { return std::move(*this).StableSort(T::GetGreater());}

        auto PartialSort(SizeType n) && -> auto { return std::move(*this).PartialSort(T::GetLess(), n); }
        auto PartialDescSort(SizeType n) && -> auto { return std::move(*this).PartialSort(T::GetGreater(), n); }
    };
}

#endif //OBJECT_ARRAY_2_3B80E429AC824537B93A1B9748FD749F
