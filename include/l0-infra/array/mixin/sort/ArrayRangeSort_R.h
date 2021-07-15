//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_2_99B07282AD86431BA6F776A589CE1BBA
#define OBJECT_ARRAY_2_99B07282AD86431BA6F776A589CE1BBA

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ArrayRangeSort_R : T {
        using typename T::OffsetType;
        using typename T::ThisType;
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

        using T::RangeSort;
        using T::SortFrom;
        using T::SortUntil;

        using T::RangeSortEx;
        using T::SortFromEx;
        using T::SortUntilEx;

        using T::RangeStableSort;
        using T::StableSortFrom;
        using T::StableSortUntil;

        using T::RangeStableSortEx;
        using T::StableSortFromEx;
        using T::StableSortUntilEx;

        using T::RangePartialSort;
        using T::PartialSortFrom;
        using T::PartialSortUntil;

        using T::RangePartialSortEx;
        using T::PartialSortFromEx;
        using T::PartialSortUntilEx;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(OffsetType from, OffsetType until, BitMap scope, LESS& less) && -> auto {
            return T::RangeSort(from, until, scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortFrom(OffsetType from, BitMap scope, LESS& less) && -> auto {
            return T::SortFrom(from, scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntil(OffsetType until, BitMap scope, LESS& less) && -> auto {
            return T::SortFrom(until, scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSortEx(OffsetType from, OffsetType until, BitMap exclude, LESS& less) && -> auto {
            return T::RangeSortEx(from, until, exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortFromEx(OffsetType from, BitMap exclude, LESS& less) && -> auto {
            return T::SortFromEx(from, exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntilEx(OffsetType until, BitMap exclude, LESS& less) && -> auto {
            return T::SortUntilEx(until, exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(OffsetType from, OffsetType until, LESS& less) && -> auto {
            return T::RangeSort(from, until, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortFrom(OffsetType from, LESS& less) && -> auto {
            return T::SortFrom(from, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntil(OffsetType until, LESS& less) && -> auto {
            return T::SortUntil(until, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(OffsetType from, OffsetType until, LESS& less) && -> auto {
            return T::RangeStableSort(from, until, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFrom(OffsetType from, LESS& less) && -> auto {
            return T::StableSortFrom(from, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntil(OffsetType until, LESS& less) && -> auto {
            return T::StableSortUntil(until, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(OffsetType from, OffsetType until, BitMap scope, LESS& less) && -> auto {
            return RangeStableSort(from, until, scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFrom(OffsetType from, BitMap scope, LESS& less) && -> auto {
            return StableSortFrom(from, scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntil(OffsetType until, BitMap scope, LESS& less) && -> auto {
            return StableSortUntil(until, scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSortEx(OffsetType from, OffsetType until, BitMap exclude, LESS& less) && -> auto {
            return RangeStableSortEx(from, until, exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFromEx(OffsetType from, BitMap exclude, LESS& less) && -> auto {
            return StableSortFromEx(from, exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntilEx(OffsetType until, BitMap exclude, LESS& less) && -> auto {
            return StableSortFromEx(until, exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(OffsetType from, OffsetType until, LESS&& less, SizeType n) && -> auto {
            return T::RangePartialSort(from, until, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFrom(OffsetType from, LESS&& less, SizeType n) && -> auto {
            return T::PartialSortFrom(from, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntil(OffsetType until, LESS&& less, SizeType n) && -> auto {
            return T::PartialSortUntil(until, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(OffsetType from, OffsetType until, BitMap scope, LESS&& less, SizeType n) && -> auto {
            return T::RangePartialSort(from, until, scope, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFrom(OffsetType from, BitMap scope, LESS&& less, SizeType n) && -> auto {
            return T::PartialSortFrom(from, scope, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntil(OffsetType until, BitMap scope, LESS&& less, SizeType n) && -> auto {
            return T::PartialSortUntil(until, scope, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSortEx(OffsetType from, OffsetType until, BitMap excluded, LESS&& less, SizeType n) && -> auto {
            return T::RangePartialSortEx(from, until, excluded, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFromEx(OffsetType from, BitMap excluded, LESS&& less, SizeType n) && -> auto {
            return T::PartialSortFromEx(from, excluded, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntilEx(OffsetType until, BitMap excluded, LESS&& less, SizeType n) && -> auto {
            return T::PartialSortUntilEx(until, excluded, std::forward<LESS>(less), n);
        }
    };
}

#endif //OBJECT_ARRAY_2_99B07282AD86431BA6F776A589CE1BBA
