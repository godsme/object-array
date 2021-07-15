//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_2_BBFBA689F2ED4999881B3238BD4D00EC
#define OBJECT_ARRAY_2_BBFBA689F2ED4999881B3238BD4D00EC

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ArrayRangeSort : T {
        using typename T::OffsetType;
        using typename T::ThisType;
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(OffsetType from, OffsetType until, BitMap scope, LESS& less) & -> ThisType & {
            T::Unsafe_RangeScopeSort(T::OffsetToIndex(from), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortFrom(OffsetType from, BitMap scope, LESS& less) & -> ThisType & {
            T::Unsafe_RangeScopeSort(T::OffsetToIndex(from), T::IndexEnd(), T::MaskScope(scope), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntil(OffsetType until, BitMap scope, LESS& less) & -> ThisType & {
            T::Unsafe_RangeScopeSort(T::IndexBegin(), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSortEx(OffsetType from, OffsetType until, BitMap exclude, LESS& less) & -> ThisType & {
            return RangeSort(from, until, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortFromEx(OffsetType from, BitMap exclude, LESS& less) & -> ThisType & {
            return SortFrom(from, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntilEx(OffsetType until, BitMap exclude, LESS& less) & -> ThisType & {
            return SortUntil(until, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(OffsetType from, OffsetType until, BitMap scope, LESS& less) & -> ThisType & {
            T::Unsafe_RangeScopeStableSort(T::OffsetToIndex(from), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFrom(OffsetType from, BitMap scope, LESS& less) & -> ThisType & {
            T::Unsafe_RangeScopeStableSort(T::OffsetToIndex(from), T::IndexEnd(), T::MaskScope(scope), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntil(OffsetType until, BitMap scope, LESS& less) & -> ThisType & {
            T::Unsafe_RangeScopeStableSort(T::IndexBegin(), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSortEx(OffsetType from, OffsetType until, BitMap exclude, LESS& less) & -> ThisType & {
            return RangeStableSort(from, until, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFromEx(OffsetType from, BitMap exclude, LESS& less) & -> ThisType & {
            return StableSortFrom(from, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntilEx(OffsetType until, BitMap exclude, LESS& less) & -> ThisType & {
            return StableSortUntil(until, ~exclude, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(OffsetType from, OffsetType until, LESS& less) & -> ThisType & {
            T::Unsafe_RangeSort(T::OffsetToIndex(from), T::OffsetToIndex(until), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortFrom(OffsetType from, LESS& less) & -> ThisType & {
            return RangeSort(from, T::IndexEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntil(OffsetType until, LESS& less) & -> ThisType & {
            return RangeSort(T::IndexBegin(), until, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(OffsetType from, OffsetType until, LESS& less) & -> ThisType & {
            T::Unsafe_RangeStableSort(T::OffsetToIndex(from), T::OffsetToIndex(until), std::forward<LESS>(less));
            return T::ToThisType();
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFrom(OffsetType from, LESS& less) & -> ThisType & {
            return RangeStableSort(from, T::IndexEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntil(OffsetType until, LESS& less) & -> ThisType & {
            return RangeStableSort(T::IndexBegin(), until, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(OffsetType from, OffsetType until, LESS&& less, SizeType n) & -> auto {
            return T::MakeSlice(T::Unsafe_RangePartialSort(T::OffsetToIndex(from), T::OffsetToIndex(until), std::forward<LESS>(less), n));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFrom(OffsetType from, LESS&& less, SizeType n) & -> auto {
            return T::MakeSlice(T::Unsafe_RangePartialSort(T::OffsetToIndex(from), T::IndexEnd(), std::forward<LESS>(less), n));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntil(OffsetType until, LESS&& less, SizeType n) & -> auto {
            return T::MakeSlice(T::Unsafe_RangePartialSort(T::IndexBegin(), T::OffsetToIndex(until), std::forward<LESS>(less), n));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(OffsetType from, OffsetType until, BitMap scope, LESS&& less, SizeType n) & -> auto {
            return T::MakeSlice(T::Unsafe_RangePartialSort(T::OffsetToIndex(from), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less), n));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFrom(OffsetType from, BitMap scope, LESS&& less, SizeType n) & -> auto {
            return T::MakeSlice(T::Unsafe_RangePartialSort(T::OffsetToIndex(from), T::IndexEnd(), T::MaskScope(scope), std::forward<LESS>(less), n));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntil(OffsetType until, BitMap scope, LESS&& less, SizeType n) & -> auto {
            return T::MakeSlice(T::Unsafe_RangePartialSort(T::IndexBegin(), T::OffsetToIndex(until), T::MaskScope(scope), std::forward<LESS>(less), n));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSortEx(OffsetType from, OffsetType until, BitMap excluded, LESS&& less, SizeType n) & -> auto {
            return RangePartialSort(from, until, ~excluded, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFromEx(OffsetType from, BitMap excluded, LESS&& less, SizeType n) & -> auto {
            return PartialSortFrom(from, ~excluded, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntilEx(OffsetType until, BitMap excluded, LESS&& less, SizeType n) & -> auto {
            return PartialSortUntil(until, ~excluded, std::forward<LESS>(less), n);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(OffsetType from, OffsetType until, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto SortFrom(OffsetType from, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntil(OffsetType until, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSortEx(OffsetType from, OffsetType until, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto SortFromEx(OffsetType from, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntilEx(OffsetType until, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeSort(OffsetType from, OffsetType until, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto SortFrom(OffsetType from, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto SortUntil(OffsetType until, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(OffsetType from, OffsetType until, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFrom(OffsetType from, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntil(OffsetType until, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSort(OffsetType from, OffsetType until, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFrom(OffsetType from, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntil(OffsetType until, BitMap scope, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto RangeStableSortEx(OffsetType from, OffsetType until, BitMap exclude, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortFromEx(OffsetType from, BitMap exclude, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto StableSortUntilEx(OffsetType until, BitMap exclude, LESS& less) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(OffsetType from, OffsetType until, LESS&& less, SizeType n) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFrom(OffsetType from, LESS&& less, SizeType n) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntil(OffsetType until, LESS&& less, SizeType n) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSort(OffsetType from, OffsetType until, BitMap scope, LESS&& less, SizeType n) && = delete;
        template<__lEsS_cOnCePt(LESS)>
        auto RangePartialSortEx(OffsetType from, OffsetType until, BitMap, LESS&& less, SizeType n) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFrom(OffsetType from, BitMap, LESS&& less, SizeType n) && = delete;
        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortFromEx(OffsetType from, BitMap, LESS&& less, SizeType n) && = delete;

        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntil(OffsetType until, BitMap scope, LESS&& less, SizeType n) && = delete;
        template<__lEsS_cOnCePt(LESS)>
        auto PartialSortUntilEx(OffsetType until, BitMap, LESS&& less, SizeType n) && = delete;
    };
}

#endif //OBJECT_ARRAY_2_BBFBA689F2ED4999881B3238BD4D00EC
