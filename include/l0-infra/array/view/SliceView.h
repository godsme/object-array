//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_SLICE_F6D83AE910B24316944139AD07DB3119
#define OBJECT_ARRAY_2_SLICE_F6D83AE910B24316944139AD07DB3119

#include <l0-infra/array/holder/SliceHolder.h>
#include <l0-infra/array/holder/FromSliceHolder.h>
#include <l0-infra/array/holder/UntilSliceHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/array_like/ConstRangeView.h>
#include <l0-infra/array/mixin/access/ArrayObjectAccessor.h>
#include <l0-infra/array/mixin/foreach/SliceSimpleForEach.h>
#include <l0-infra/array/mixin/foreach/SliceScopedForEach.h>
#include <l0-infra/array/mixin/foreach/SimpleForEachExt.h>
#include <l0-infra/array/mixin/foreach/ScopedForEachExt.h>
#include <l0-infra/array/mixin/min/SliceMinElem.h>
#include <l0-infra/array/mixin/find/SliceNonScopeFind.h>
#include <l0-infra/array/mixin/find/SliceScopeFind.h>
#include <l0-infra/array/mixin/sort/SliceSort.h>
#include <l0-infra/array/mixin/factory/SliceMaker.h>
#include <l0-infra/array/mixin/min/UnsafeSliceScopeMinElem.h>
#include <l0-infra/array/mixin/factory/WithIndexViewFactory_R.h>
#include <l0-infra/array/mixin/foreach/UnsafeSliceScopedForEach.h>
#include <l0-infra/array/mixin/foreach/UnsafeScopeForEach.h>
#include <l0-infra/array/mixin/access/RangeExporter.h>
#include <l0-infra/array/mixin/iterable/IterableArrayLike.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/find/UnsafeScopedFind.h>
#include <l0-infra/array/mixin/find/ScopeFindExt.h>
#include <l0-infra/array/mixin/min/SimpleMinElemExt.h>
#include <l0-infra/array/mixin/min/ScopedMinElemExt.h>
#include <l0-infra/array/mixin/factory/ScopeViewFactory.h>
#include <l0-infra/array/mixin/factory/ScopeViewFactory_R.h>
#include <l0-infra/array/mixin/factory/MinElemsFactory.h>
#include <l0-infra/array/mixin/factory/SortViewFactory.h>
#include <l0-infra/array/mixin/factory/MinElemsFactory_R.h>
#include <l0-infra/array/mixin/factory/SortViewFactory_R.h>
#include <l0-infra/array/mixin/sort/SliceUnsafeScopeSort.h>
#include <l0-infra/array/mixin/find/UnsafeSliceScopedFind.h>
#include <l0-infra/array/mixin/sort/BasicSort.h>
#include <l0-infra/array/mixin/sort/BasicSort_R.h>
#include <l0-infra/array/mixin/append/ViewAppend.h>
#include <l0-infra/array/mixin/replace/ViewReplace.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/less/ViewObjectLess.h>
#include <l0-infra/array/mixin/eq/ViewObjectEquality.h>
#include <l0-infra/array/mixin/rotate/ViewUnsafeRotate.h>
#include <l0-infra/array/mixin/rotate/Rotate.h>
#include <l0-infra/array/mixin/rotate/Rotate_R.h>
#include <l0-infra/array/mixin/erase/RangeViewClearIf.h>
#include <l0-infra/array/mixin/erase/RangeViewClear.h>
#include <l0-infra/array/mixin/factory/ViewEnumViewFactory.h>

namespace slice {
    using Private = ::mixin::Private<
            mixin::ViewedArray,
            mixin::ViewObjectLess,
            mixin::ViewObjectEquality,
            mixin::ObjectCompareExt,
            mixin::ConstRangeView,
            mixin::ArrayObjectAccessor,
            mixin::SliceSimpleForEach,
            mixin::UnsafeSliceScopedForEach,
            mixin::SliceScopedForEach,
            mixin::SliceScopeFind,
            mixin::SliceMaker,
            mixin::___mutable_mixin_delimiter___,
            mixin::SliceSort,
            mixin::ViewUnsafeRotate>;

    using Public = ::mixin::Public<
            mixin::RangeExporter,
            mixin::ByIndexRefAccessor,
            mixin::ByIndexAccessor,
            mixin::IterableIndexBasedArray,
            mixin::RangedElemCount,
            mixin::ElemCountExt,
            mixin::SimpleForEachExt,
            mixin::ScopedForEachExt,
            mixin::UnsafeScopedForEach,

            mixin::SliceNonScopeFind,
            mixin::SimpleFindExt,
            mixin::UnsafeSliceScopedFind,
            mixin::ScopeFindExt,

            mixin::SliceMinElem,
            mixin::SimpleMinElemExt,
            mixin::UnsafeSliceScopeMinElem,
            mixin::ScopedMinElemExt,

            mixin::WithIndexViewFactory_R,
            mixin::EnumViewFactory,
            mixin::ScopeViewFactory,
            mixin::ScopeViewFactory_R,
            mixin::MinElemsFactory,
            mixin::MinElemsFactory_R,
            mixin::SortViewFactory,
            mixin::SortViewFactory_R,
            mixin::___mutable_mixin_delimiter___,
            mixin::ViewAppend,
            mixin::AppendExt,
            mixin::ViewReplace,
            mixin::ReplaceExt,
            mixin::RangeViewClear,
            mixin::RangeViewClearIf,
            mixin::SliceUnsafeScopeSort,
            mixin::BasicSort,
            mixin::BasicSort_R,
            mixin::SortExt,
            mixin::SortExt_R,
            mixin::Rotate,
            mixin::Rotate_R>;

    template<typename HOLDER>
    class Array : public Public::Compose<HOLDER, Private, Array<HOLDER>> {
        using Parent = Public::Compose<HOLDER, Private, Array<HOLDER>>;
    public:
        using Parent::Parent;

    private:
        template<typename>
        friend class mixin::ViewObjectLess;

        template<typename>
        friend class mixin::ViewObjectEquality;
    };
}

template<typename ARRAY>
using ValueSliceView = slice::Array<typename holder::Slice<ARRAY>::ValueView>;

template<typename ARRAY>
using RefSliceView = slice::Array<typename holder::Slice<ARRAY>::RefView>;

template<typename ARRAY>
using ValueFromSliceView = slice::Array<typename holder::FromSlice<ARRAY>::ValueView>;

template<typename ARRAY>
using RefFromSliceView = slice::Array<typename holder::FromSlice<ARRAY>::RefView>;

template<typename ARRAY>
using ValueUntilSliceView = slice::Array<typename holder::UntilSlice<ARRAY>::ValueView>;

template<typename ARRAY>
using RefUntilSliceView = slice::Array<typename holder::UntilSlice<ARRAY>::RefView>;

#endif //OBJECT_ARRAY_2_SLICE_F6D83AE910B24316944139AD07DB3119
