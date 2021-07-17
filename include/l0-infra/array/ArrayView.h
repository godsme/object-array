//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_EF20B2BF9E0249DA8F02F690E18C3BCE
#define OBJECT_ARRAY_2_EF20B2BF9E0249DA8F02F690E18C3BCE

#include <l0-infra/array/holder/ArrayViewHolder.h>
#include <l0-infra/array/holder/ConstArrayViewHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <l0-infra/array/mixin/array_like/ArrayLike.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayLike.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayRange.h>
#include <l0-infra/array/mixin/access/RangeExporter.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/append/SimpleAppend.h>
#include <l0-infra/array/mixin/sort/ContiguousRangeSort.h>
#include <l0-infra/array/mixin/access/ByIndexRefAccessor.h>
#include <l0-infra/array/mixin/access/ByIndexAccessor.h>
#include <l0-infra/array/mixin/count/RangedElemCount.h>
#include <l0-infra/array/mixin/append/AppendExporter.h>
#include <l0-infra/array/mixin/index/ObjectIndex.h>
#include <l0-infra/array/mixin/foreach/ArrayElemVisit.h>
#include <l0-infra/array/mixin/foreach/SimpleRangeForEach.h>
#include <l0-infra/array/mixin/foreach/UnsafeRangeScopeForEach.h>
#include <l0-infra/array/mixin/foreach/SimpleForEach.h>
#include <l0-infra/array/mixin/foreach/SimpleForEachExt.h>
#include <l0-infra/array/mixin/foreach/ArrayScopedForEach.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/min/ContiguousRangeMinElem.h>
#include <l0-infra/array/mixin/min/UnsafeRangeScopeMinElem.h>
#include <l0-infra/array/mixin/min/SimpleMinElem.h>
#include <l0-infra/array/mixin/min/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/min/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/find/UnsafeRangeFind.h>
#include <l0-infra/array/mixin/find/UnsafeScopedRangeFind.h>
#include <l0-infra/array/mixin/find/NonScopedSimpleFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/find/UnsafeScopedFind.h>
#include <l0-infra/array/mixin/find/ScopeFindExt.h>
#include <l0-infra/array/mixin/erase/SimpleErase.h>
#include <l0-infra/array/mixin/erase/RangedClear.h>
#include <l0-infra/array/mixin/erase/ClearExt.h>
#include <l0-infra/array/mixin/factory/MinElemsFactory.h>
#include <l0-infra/array/mixin/factory/SortViewFactory.h>
#include <l0-infra/array/mixin/iterable/IterableArrayLike.h>
#include <l0-infra/array/mixin/eq/ArrayEquality.h>
#include <l0-infra/array/mixin/factory/WithIndexViewFactory.h>
#include <l0-infra/array/mixin/foreach/UnsafeRangeForEach.h>
#include <l0-infra/array/mixin/factory/ArraySliceMaker.h>
#include <l0-infra/array/mixin/sort/ArraySort.h>
#include <l0-infra/array/mixin/sort/SortExt.h>
#include <l0-infra/array/mixin/factory/SliceViewFactory.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/erase/ScopeCleanUp.h>
#include <l0-infra/array/mixin/foreach/UnsafeScopeForEach.h>
#include <l0-infra/array/mixin/min/UnsafeArrayScopeMinElem.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/factory/ScopeViewFactory.h>
#include <l0-infra/array/mixin/sort/UnsafeRangeScopeSort.h>
#include <l0-infra/array/mixin/sort/UnSafeScopeSort.h>
#include <l0-infra/array/mixin/access/ArrayByIndexAccessor.h>
#include <l0-infra/array/mixin/count/ArrayElemCount.h>
#include <l0-infra/array/mixin/count/ElemCountExt.h>
#include <l0-infra/array/mixin/sort/BasicSort.h>
#include <l0-infra/array/mixin/replace/SimpleReplace.h>
#include <l0-infra/array/mixin/factory/SliceViewFactory_R.h>
#include <l0-infra/array/mixin/array_like/ValueArrayLike.h>
#include <l0-infra/array/mixin/less/ObjectLess.h>
#include <l0-infra/array/mixin/eq/ObjectEquality.h>
#include <l0-infra/array/mixin/eq/ObjectCompareExt.h>
#include <l0-infra/array/mixin/rotate/ArrayRangeRotate.h>
#include <l0-infra/array/mixin/rotate/Rotate.h>
#include <l0-infra/array/mixin/rotate/Rotate_R.h>
#include <l0-infra/array/mixin/rotate/RangeRotateExt.h>
#include <l0-infra/array/mixin/rotate/RangeRotateExt_R.h>
#include <l0-infra/array/mixin/count/ArrayOffsetToIndex.h>
#include <l0-infra/array/mixin/sort/ArrayRangeSort.h>
#include <l0-infra/array/mixin/sort/ArrayRangeSort_R.h>
#include <l0-infra/array/mixin/min/ArrayRangeMinElem.h>
#include <l0-infra/array/mixin/erase/UnsafeArrayRangeCleanUpIf.h>
#include <l0-infra/array/mixin/erase/ArrayRangeCleanUpIf.h>
#include <l0-infra/array/mixin/erase/ArrayRangeCleanUpIf_R.h>
#include <l0-infra/array/mixin/erase/ClearExt_R.h>

namespace array_view {
    using Private = ::mixin::Private<
            mixin::ObjectLess,
            mixin::ObjectEquality,
            mixin::ObjectCompareExt,
            mixin::ConstArrayLike,
            mixin::ContiguousArrayLike,
            mixin::ContiguousArrayRange,
            mixin::ArraySliceMaker,
            mixin::ArrayOffsetToIndex,

            mixin::ArrayElemVisit,
            mixin::SimpleRangeForEach,
            mixin::SimpleForEach,
            mixin::___mutable_mixin_delimiter___,
            mixin::ValueArrayLike,
            mixin::ArrayRangeRotate>;

    using Public = ::mixin::Public<
            mixin::ObjectIndex,
            mixin::RangeExporter,
            mixin::ByIndexRefAccessor,
            mixin::ArrayByIndexAccessor,
            mixin::ArrayElemCount,
            mixin::ElemCountExt,
            mixin::IterableArrayLike,

            mixin::UnsafeRangeFind,
            mixin::NonScopedSimpleFind,
            mixin::UnsafeScopedRangeFind,
            mixin::SimpleFindExt,
            mixin::UnsafeScopedFind,
            mixin::ScopeFindExt,
            mixin::ArrayEquality,

            mixin::UnsafeRangeScopeForEach,
            mixin::ArrayScopedForEach,
            mixin::UnsafeRangeForEach,
            mixin::UnsafeScopedForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedForEachExt,

            mixin::UnsafeRangeScopeMinElem,
            mixin::ContiguousRangeMinElem,
            mixin::ArrayRangeMinElem,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::UnsafeArrayScopeMinElem,
            mixin::ScopedMinElemExt,
            mixin::WithIndexViewFactory_R,

            mixin::SliceViewFactory,
            mixin::SliceViewFactory_R,

            mixin::ScopeViewFactory,
            mixin::ScopeViewFactory_R,

            mixin::MinElemsFactory,
            mixin::MinElemsFactory_R,
            mixin::SortViewFactory,
            mixin::SortViewFactory_R,

            mixin::___mutable_mixin_delimiter___,

            mixin::SimpleAppend,
            mixin::AppendExt,

            mixin::SimpleReplace,
            mixin::ReplaceExt,

            mixin::SimpleErase,
            mixin::EraseExt,

            mixin::UnsafeArrayRangeCleanUpIf,
            mixin::ArrayRangeCleanUpIf,
            mixin::ArrayRangeCleanUpIf_R,

            mixin::RangedClear,
            mixin::ClearExt,
            mixin::ClearExt_R,
            mixin::ScopeCleanUp,

            mixin::ContiguousRangeSort,
            mixin::UnsafeRangeScopeSort,
            mixin::UnsafeScopeSort,
            mixin::ArrayRangeSort,
            mixin::ArrayRangeSort_R,
            mixin::ArraySort,
            mixin::BasicSort,
            mixin::BasicSort_R,
            mixin::SortExt,
            mixin::SortExt_R,

            mixin::RangeRotateExt,
            mixin::RangeRotateExt_R,
            mixin::Rotate,
            mixin::Rotate_R>;

    template<typename HOLDER>
    struct Array : Public::Compose<HOLDER, Private, Array<HOLDER>> {
        using Parent = Public::Compose<HOLDER, Private, Array<HOLDER>>;
        using Parent::Parent;

    private:
        template<typename>
        friend class mixin::ViewObjectLess;

        template<typename>
        friend class mixin::ViewObjectEquality;
    };

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename WRAPPER = T, bool ORDERED = false>
    using ArrayView =  Array<holder::ArrayViewHolder<T, SIZE_TYPE, MAX_NUM, WRAPPER, ORDERED>>;

    template<typename T, std::size_t MAX_NUM, typename WRAPPER = T, bool ORDERED = false>
    using ConstArrayView = Array<holder::ConstArrayViewHolder<T, MAX_NUM, WRAPPER, ORDERED>>;

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename WRAPPER, bool ORDERED, bool = std::is_const_v<T>>
    struct ArrayViewTrait {
        using Type = ConstArrayView<T, MAX_NUM, WRAPPER, ORDERED>;
    };

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename WRAPPER, bool ORDERED>
    struct ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, WRAPPER, ORDERED, false> {
        using Type = ArrayView<T, SIZE_TYPE, MAX_NUM, WRAPPER, ORDERED>;
    };
}

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = T, bool ORDERED = false,
        typename Parent = typename array_view::ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, ELEM, ORDERED>::Type>
struct ArrayView  : Parent {
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ArrayView(T (&)[MAX_NUM], SIZE_TYPE& size) -> ArrayView<T, SIZE_TYPE, MAX_NUM, T, false>;

template<typename T, std::size_t MAX_NUM, typename WRAPPER = T, bool ORDERED = false,
        typename Parent = array_view::ConstArrayView<T, MAX_NUM, WRAPPER, ORDERED>>
struct ConstArrayView : Parent {
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ConstArrayView(T const (&)[MAX_NUM], SIZE_TYPE) -> ConstArrayView<T, MAX_NUM, T>;

#endif //OBJECT_ARRAY_2_EF20B2BF9E0249DA8F02F690E18C3BCE
