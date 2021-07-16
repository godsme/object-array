//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_A8DF9DFA5F6B4ACBB8C82416E45AD2F2
#define OBJECT_ARRAY_2_A8DF9DFA5F6B4ACBB8C82416E45AD2F2

#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayRange.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/array_like/IndexedArrayLike.h>
#include <l0-infra/array/mixin/append/IndicesAppend.h>
#include <l0-infra/array/mixin/access/ByIndexAccessor.h>
#include <l0-infra/array/mixin/access/ByIndexRefAccessor.h>
#include <l0-infra/array/mixin/append/AppendExporter.h>
#include <l0-infra/array/mixin/count/RangedElemCount.h>
#include <l0-infra/array/mixin/sort/UnsafeIndicesRangeSort.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/foreach/IndicesRangeForEach.h>
#include <l0-infra/array/mixin/foreach/IndicesOp.h>
#include <l0-infra/array/mixin/foreach/UnsafeIndicesScopedRangeForEach.h>
#include <l0-infra/array/mixin/less/IndicesLess.h>
#include <l0-infra/array/mixin/min/UnsafeIndicesRangeMinElem.h>
#include <l0-infra/array/mixin/min/UnsafeIndicesScopedRangedMinElem.h>
#include <l0-infra/array/mixin/find/UnsafeIndicesRangeFind.h>
#include <l0-infra/array/mixin/find/IndicesPred.h>
#include <l0-infra/array/mixin/find/UnsafeIndicesScopedRangeFind.h>
#include <l0-infra/array/mixin/find/UnsafeScopedFind.h>
#include <l0-infra/array/mixin/foreach/SimpleForEach.h>
#include <l0-infra/array/mixin/foreach/ArrayScopedForEach.h>
#include <l0-infra/array/mixin/find/NonScopedSimpleFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/find/ScopeFindExt.h>
#include <l0-infra/array/mixin/foreach/SimpleForEachExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/min/SimpleMinElem.h>
#include <l0-infra/array/mixin/min/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/min/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/access/IndexedObjectAccessor.h>
#include <l0-infra/array/mixin/erase/IndicesErase.h>
#include <l0-infra/array/mixin/replace/IndicesReplace.h>
#include <l0-infra/array/mixin/sort/UnsafeIndicesRangeScopeSort.h>
#include <l0-infra/array/mixin/erase/IndicesRangeClear.h>
#include <l0-infra/array/mixin/index/IndicesArrayObjectIndex.h>
#include <l0-infra/array/mixin/rotate/IndicesRangeRotate.h>
#include <l0-infra/array/mixin/factory/ArraySliceMaker.h>
#include <l0-infra/array/mixin/less/OrderedArrayLike.h>
#include <l0-infra/array/mixin/eq/OrderedObjectEquality.h>
#include <l0-infra/array/mixin/min/UnsafeArrayScopeMinElem.h>
#include <l0-infra/array/mixin/factory/SliceViewFactory.h>
#include <l0-infra/array/mixin/eq/ArrayEquality.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/erase/ScopeCleanUp.h>
#include <l0-infra/array/mixin/sort/UnSafeScopeSort.h>
#include <l0-infra/array/mixin/sort/ArraySort.h>
#include <l0-infra/array/mixin/rotate/RangeRotateExt.h>
#include <l0-infra/array/mixin/count/ArrayOffsetToIndex.h>
#include <l0-infra/array/mixin/sort/ArrayRangeSort.h>
#include <l0-infra/array/mixin/min/ArrayRangeMinElem.h>
#include <l0-infra/array/mixin/replace/OrderedReplaceLastIf.h>

namespace indexed_array {
    using Private = ::mixin::Private<
            mixin::OrderedArrayLike,
            mixin::OrderedObjectEquality,
            mixin::ViewedArray,
            mixin::IndexedArrayLike,
            mixin::IndexedObjectAccessor,
            mixin::ArraySliceMaker,
            mixin::ArrayOffsetToIndex,
            mixin::ContiguousArrayRange,
            mixin::IndicesOp,
            mixin::IndicesLess,
            mixin::IndicesPred,
            mixin::IndicesRangeForEach,
            mixin::SimpleForEach,
            mixin::IndicesRangeRotate>;

    using Public = ::mixin::Public<
            mixin::ObjectCompareExt,
            mixin::RangeExporter,
            mixin::IndicesArrayObjectIndex,
            mixin::ByIndexRefAccessor,
            mixin::ArrayByIndexAccessor,
            mixin::ArrayElemCount,
            mixin::ElemCountExt,
            mixin::IterableIndexBasedArray,

            mixin::UnsafeIndicesRangeFind,
            mixin::NonScopedSimpleFind,
            mixin::UnsafeIndicesScopedRangeFind,
            mixin::UnsafeScopedFind,
            mixin::SimpleFindExt,
            mixin::ScopeFindExt,

            mixin::UnsafeIndicesScopedRangeForEach,
            mixin::UnsafeRangeForEach,
            mixin::ArrayScopedForEach,
            mixin::UnsafeScopedForEach,
            mixin::SimpleForEachExt,
            mixin::ScopedForEachExt,

            mixin::UnsafeIndicesRangeMinElem,
            mixin::UnsafeIndicesScopedRangeMinElem,
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

            mixin::ArrayEquality,
            mixin::___mutable_mixin_delimiter___,
            mixin::IndicesReplace,
            mixin::OrderedReplaceLastIf,
            mixin::ReplaceExt,
            mixin::IndicesAppend,
            mixin::AppendExt,
            mixin::IndicesErase,
            mixin::EraseExt,
            mixin::IndicesRangedClear,
            mixin::ClearExt,
            mixin::ScopeCleanUp,
            mixin::UnsafeIndicesRangeSort,
            mixin::UnsafeIndicesRangeScopeSort,
            mixin::UnsafeScopeSort,
            mixin::ArrayRangeSort,
            mixin::ArraySort,
            mixin::BasicSort,
            mixin::SortExt,
            mixin::RangeRotateExt,
            mixin::Rotate>;
}

#endif //OBJECT_ARRAY_2_A8DF9DFA5F6B4ACBB8C82416E45AD2F2
