//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_A6C7AD27907C408D9EE65139A030C61B
#define OBJECT_ARRAY_2_A6C7AD27907C408D9EE65139A030C61B

#include <l0-infra/array/holder/DynamicArrayHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/PointerArrayLike.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayRange.h>
#include <l0-infra/array/mixin/factory/ArraySliceMaker.h>
#include <l0-infra/array/mixin/access/PointerArrayObjectAccessor.h>
#include <l0-infra/array/mixin/index/DynamicObjectIndex.h>
#include <l0-infra/array/mixin/eq/ArrayEquality.h>
#include <l0-infra/array/mixin/min/UnsafeArrayScopeMinElem.h>
#include <l0-infra/array/mixin/factory/SliceViewFactory.h>
#include <l0-infra/array/mixin/append/ProxyAppend.h>
#include <l0-infra/array/ObjectArray.h>
#include <l0-infra/array/mixin/erase/DynamicRangedClear.h>
#include <l0-infra/array/mixin/sort/UnsafeIndicesRangeScopeSort.h>
#include <l0-infra/array/mixin/sort/UnsafePointersRangeSort.h>
#include <l0-infra/array/mixin/sort/UnsafePointersRangeScopeSort.h>
#include <l0-infra/array/mixin/find/UnsafePointerRangeFind.h>
#include <l0-infra/array/mixin/foreach/UnsafePointerRangeScopeForEach.h>
#include <l0-infra/array/mixin/min/UnsafePointersRangeMinElem.h>
#include <l0-infra/array/mixin/min/UnsafePointerRangeScopeMinElem.h>
#include <l0-infra/array/mixin/rotate/PointersRangeRotate.h>
#include <l0-infra/array/mixin/less/PointerLess.h>
#include <l0-infra/array/mixin/replace/ProxyReplace.h>
#include <l0-infra/array/mixin/find/PointerPred.h>

namespace dynamic_array {
    using Private = ::mixin::Private<
            mixin::ObjectLess,
            mixin::ObjectEquality,
            mixin::ObjectCompareExt,
            mixin::PointerArrayLike,
            mixin::ContiguousArrayRange,
            mixin::PointerArrayObjectAccessor,
            mixin::ArraySliceMaker,
            mixin::ArrayOffsetToIndex,
            mixin::PointerLess,
            mixin::PointerPred,

            mixin::ArrayElemVisit,
            mixin::SimpleRangeForEach,
            mixin::SimpleForEach,
            mixin::___mutable_mixin_delimiter___,
            mixin::PointersRangeRotate>;

    using Public = ::mixin::Public<
            mixin::RangeExporter,
            mixin::DynamicArrayObjectIndex,
            mixin::ByIndexRefAccessor,
            mixin::ArrayByIndexAccessor,
            mixin::ArrayElemCount,
            mixin::ElemCountExt,
            mixin::IterableIndexBasedArray,

            mixin::UnsafePointerRangeFind,
            mixin::NonScopedSimpleFind,
            mixin::UnsafeScopedRangeFind,
            mixin::SimpleFindExt,
            mixin::UnsafeScopedFind,
            mixin::ScopeFindExt,

            mixin::ArrayEquality,

            mixin::UnsafePointerScopedRangeForEach,
            mixin::ArrayScopedForEach,
            mixin::UnsafeRangeForEach,
            mixin::UnsafeScopedForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedForEachExt,

            mixin::UnsafePointerScopedRangeMinElem,
            mixin::UnsafePointerRangeMinElem,
            mixin::ArrayRangeMinElem,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::UnsafeArrayScopeMinElem,
            mixin::ScopedMinElemExt,

            mixin::WithIndexViewFactory,
            mixin::SliceViewFactory,
            mixin::ScopeViewFactory,
            mixin::MinElemsFactory,
            mixin::SortViewFactory,

            mixin::___mutable_mixin_delimiter___,

            mixin::ProxyAppend,
            mixin::AppendExt,
            mixin::ProxyReplace,
            mixin::ReplaceExt,
            mixin::ProxyErase,
            mixin::EraseExt,
            mixin::DynamicRangedClear,
            mixin::ClearExt,
            mixin::ScopeCleanUp,
            mixin::UnsafeArrayRangeCleanUpIf,
            mixin::ArrayRangeCleanUpIf,

            mixin::UnsafePointersRangeSort,
            mixin::UnsafePointersRangeScopeSort,
            mixin::UnsafeScopeSort,
            mixin::ArrayRangeSort,
            mixin::ArraySort,
            mixin::BasicSort,
            mixin::SortExt,
            mixin::RangeRotateExt,
            mixin::Rotate>;

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
}

template<typename ALLOCATOR, std::size_t MAX_NUM, bool FREE_ON_DTOR = true,
        typename Parent = dynamic_array::Array<::holder::DynamicArrayHolder<ALLOCATOR, ObjectArray<typename ALLOCATOR::ObjectType*, MAX_NUM>, FREE_ON_DTOR>>>
struct DynamicArray : Parent {
    DynamicArray(ALLOCATOR& allocator) : Parent(allocator) {}
};

#endif //OBJECT_ARRAY_2_A6C7AD27907C408D9EE65139A030C61B
