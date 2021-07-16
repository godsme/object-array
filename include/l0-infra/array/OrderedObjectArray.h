//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_ORDEREDARRAY_A1E87B67F6ED446382432020F2A36B1E
#define OBJECT_ARRAY_2_ORDEREDARRAY_A1E87B67F6ED446382432020F2A36B1E

#include <l0-infra/array/holder/OrderedArrayHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/array_like/ArrayLike.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayLike.h>
#include <l0-infra/array/mixin/append/OrderedAppend.h>
#include <l0-infra/array/mixin/sort/ContiguousRangeSort.h>
#include <l0-infra/array/mixin/access/ByIndexAccessor.h>
#include <l0-infra/array/mixin/access/ByIndexRefAccessor.h>
#include <l0-infra/array/mixin/append/AppendExporter.h>
#include <l0-infra/array/mixin/count/RangedElemCount.h>
#include <l0-infra/array/mixin/array_like/ContiguousArrayRange.h>
#include <l0-infra/array/mixin/index/ObjectIndex.h>
#include <l0-infra/array/mixin/foreach/ArrayElemVisit.h>
#include <l0-infra/array/mixin/foreach/SimpleRangeForEach.h>
#include <l0-infra/array/mixin/find/UnsafeRangeFind.h>
#include <l0-infra/array/mixin/factory/ArraySliceMaker.h>
#include <l0-infra/array/mixin/min/ContiguousRangeMinElem.h>
#include <l0-infra/array/mixin/foreach/UnsafeRangeScopeForEach.h>
#include <l0-infra/array/mixin/find/UnsafeScopedRangeFind.h>
#include <l0-infra/array/mixin/min/UnsafeRangeScopeMinElem.h>
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
#include <l0-infra/array/mixin/access/RangeExporter.h>
#include <l0-infra/array/mixin/foreach/UnsafeRangeForEach.h>
#include <l0-infra/array/mixin/eq/ArrayEquality.h>
#include <l0-infra/array/mixin/min/UnsafeArrayScopeMinElem.h>
#include <l0-infra/array/mixin/factory/SliceViewFactory.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/erase/ScopeCleanUp.h>
#include <l0-infra/array/mixin/sort/UnsafeRangeScopeSort.h>
#include <l0-infra/array/mixin/sort/UnSafeScopeSort.h>
#include <l0-infra/array/mixin/sort/ArraySort.h>
#include <l0-infra/array/mixin/replace/OrderedReplace.h>
#include <l0-infra/array/mixin/erase/OrderedErase.h>
#include <l0-infra/array/mixin/eq/OrderedObjectEquality.h>
#include <l0-infra/array/mixin/eq/ObjectCompareExt.h>
#include <l0-infra/array/mixin/rotate/ArrayRangeRotate.h>
#include <l0-infra/array/mixin/rotate/Rotate.h>
#include <l0-infra/array/mixin/rotate/RangeRotateExt.h>
#include <l0-infra/array/mixin/sort/ArrayRangeSort.h>
#include <l0-infra/array/mixin/count/ArrayOffsetToIndex.h>
#include <l0-infra/array/mixin/min/ArrayRangeMinElem.h>
#include <l0-infra/array/mixin/replace/OrderedReplaceLastIf.h>

namespace ordered_array {
    using Private = ::mixin::Private<
            mixin::OrderedArrayLike,
            mixin::OrderedObjectEquality,
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
            mixin::ArrayLike,
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

            mixin::WithIndexViewFactory,
            mixin::SliceViewFactory,
            mixin::ScopeViewFactory,
            mixin::MinElemsFactory,
            mixin::SortViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::OrderedReplace,
            mixin::ReplaceExt,
            mixin::OrderedReplaceLastIf,
            mixin::OrderedAppend,
            mixin::AppendExt,
            mixin::OrderedErase,
            mixin::EraseExt,
            mixin::RangedClear,
            mixin::ClearExt,
            mixin::ScopeCleanUp,
            mixin::ContiguousRangeSort,
            mixin::UnsafeRangeScopeSort,
            mixin::UnsafeScopeSort,
            mixin::ArrayRangeSort,
            mixin::ArraySort,
            mixin::BasicSort,
            mixin::SortExt,
            mixin::RangeRotateExt,
            mixin::Rotate>;

    template<typename HOLDER>
    class Array : public Public::Compose<HOLDER, Private, Array<HOLDER>> {
        using Parent = Public::Compose<HOLDER, Private, Array<HOLDER>>;

        using typename Parent::Mixins;

    public:
        using typename Parent::ObjectType;
        using Mixins::GetLess;

    public:
        using Parent::Parent;

        Array() {}
        Array(std::initializer_list<ObjectType> l) {
            auto n = 0;
            for(auto i = l.begin(); i != l.end(); ++i) {
                Parent::Append(*i);
                if(++n == Parent::MAX_SIZE) break;;
            }
        }

    private:
        template<typename>
        friend class mixin::ViewObjectLess;

        template<typename>
        friend class mixin::ViewObjectEquality;
    };
}

template<typename OBJ, std::size_t MAX_NUM, typename LESS = std::less<OBJ>>
using OrderedObjectArray = ordered_array::Array<holder::OrderedArrayHolder<OBJ, MAX_NUM, LESS>>;

#endif //OBJECT_ARRAY_2_ORDEREDARRAY_A1E87B67F6ED446382432020F2A36B1E
