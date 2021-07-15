//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_CF9C49540ACB4E01BF770676F5A4B99B
#define OBJECT_ARRAY_2_CF9C49540ACB4E01BF770676F5A4B99B

#include <l0-infra/array/holder/SortViewHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/access/ArrayObjectAccessor.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/array_like/IndexedArrayLike.h>
#include <l0-infra/array/mixin/foreach/SortViewIndicesOp.h>
#include <l0-infra/array/mixin/less/IndicesLess.h>
#include <l0-infra/array/mixin/find/SortViewIndicesPred.h>
#include <l0-infra/array/mixin/foreach/IndicesRangeForEach.h>
#include <l0-infra/array/mixin/iterable/IterableIndexBasedArray.h>
#include <l0-infra/array/mixin/min/UnsafeIndicesRangeMinElem.h>
#include <l0-infra/array/mixin/find/UnsafeIndicesRangeFind.h>
#include <l0-infra/array/mixin/sort/IndicesRangeInit.h>
#include <l0-infra/array/mixin/sort/UnsafeIndicesRangeSort.h>
#include <l0-infra/array/mixin/sort/SortViewSort.h>
#include <l0-infra/array/mixin/sort/IndicesRangeScopeInit.h>
#include <l0-infra/array/mixin/sort/SortExt.h>
#include <l0-infra/array/mixin/iterable/IterableWithIndexArrayLike.h>
#include <l0-infra/array/mixin/factory/WithIndexViewFactory_R.h>
#include <l0-infra/array/mixin/sort/SortExt_R.h>
#include <l0-infra/array/mixin/access/SortViewByIndexRefAccessor.h>
#include <l0-infra/array/mixin/iterable/IterableSortView.h>
#include <l0-infra/array/mixin/access/ArrayByIndexAccessor.h>
#include <l0-infra/array/mixin/count/ArrayElemCount.h>
#include <l0-infra/array/mixin/count/ElemCountExt.h>
#include <l0-infra/array/mixin/less/ViewObjectLess.h>
#include <l0-infra/array/mixin/eq/ViewObjectEquality.h>
#include <l0-infra/array/mixin/eq/ObjectCompareExt.h>

namespace sort_view {
    template<template<typename> typename INDICES_INIT>
    using Private = ::mixin::Private<
            mixin::ViewedArray,
            mixin::ViewObjectLess,
            mixin::ViewObjectEquality,
            mixin::ObjectCompareExt,
            mixin::IndexedArrayLike,
            mixin::ArrayObjectAccessor,
            mixin::ViewedRange,
            mixin::SortViewIndicesOp,
            mixin::IndicesLess,
            mixin::SortViewIndicesPred,
            mixin::IndicesRangeForEach,
            mixin::UnsafeIndicesRangeFind,
            mixin::SimpleForEach,
            mixin::UnsafeIndicesRangeMinElem,
            mixin::___mutable_mixin_delimiter___,
            INDICES_INIT,
            mixin::UnsafeIndicesRangeSort>;

    using Public = ::mixin::Public<
            mixin::RangeExporter,
            mixin::SortViewByIndexRefAccessor,
            mixin::ArrayByIndexAccessor,
            mixin::IterableSortView,
            mixin::SortViewWithIndexViewFactory_R,
            mixin::ArrayElemCount,
            mixin::ElemCountExt,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::___mutable_mixin_delimiter___,
            mixin::SortViewSort,
            mixin::SortExt,
            mixin::SortExt_R>;

    template<typename HOLDER, template<typename> typename INDICES_INIT>
    class Array : public Public::Compose<HOLDER, Private<INDICES_INIT>, Array<HOLDER, INDICES_INIT>> {
        using Parent = Public::Compose<HOLDER, Private<INDICES_INIT>, Array<HOLDER, INDICES_INIT>>;

    public:
        using typename Parent::Mixins;
        using Parent::Parent;
        using Mixins::GetIndices;
        using Mixins::GetArray;

    private:
        template<typename>
        friend class mixin::ViewObjectLess;

        template<typename>
        friend class mixin::ViewObjectEquality;
    };

    template<template<typename> typename INDICES_INIT>
    struct SortView {
        template <typename ARRAY>
        using ValueView = sort_view::Array<typename holder::SortView<ARRAY>::ValueView, INDICES_INIT>;
        template <typename ARRAY>
        using RefView = sort_view::Array<typename holder::SortView<ARRAY>::RefView, INDICES_INIT>;
    };
}

using SortView = sort_view::SortView<mixin::IndicesRangeInit>;
using ScopeSortView = sort_view::SortView<mixin::IndicesRangeScopeInit>;

#endif //OBJECT_ARRAY_2_CF9C49540ACB4E01BF770676F5A4B99B
