//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_AF881B1A6C05426D9E9034C73574A55C
#define OBJECT_ARRAY_2_AF881B1A6C05426D9E9034C73574A55C

#include <l0-infra/array/holder/ScopeViewHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ScopedArrayLike.h>
#include <l0-infra/array/mixin/array_like/ViewedArray.h>
#include <l0-infra/array/mixin/access/ArrayObjectAccessor.h>
#include <l0-infra/array/mixin/foreach/ScopeSimpleForEach.h>
#include <l0-infra/array/mixin/foreach/SimpleForEachExt.h>
#include <l0-infra/array/mixin/count/ScopedElemCount.h>
#include <l0-infra/array/mixin/array_like/ViewedArrayRange.h>
#include <l0-infra/array/mixin/find/ScopedSimpleFind.h>
#include <l0-infra/array/mixin/iterable/IterableScopedArrayLike.h>
#include <l0-infra/array/mixin/factory/WithIndexScopeArrayLikeFactory_R.h>
#include <l0-infra/array/mixin/factory/SortViewFactory.h>
#include <l0-infra/array/mixin/factory/SortViewFactory_R.h>
#include <l0-infra/array/mixin/factory/MinElemsFactory.h>
#include <l0-infra/array/mixin/factory/MinElemsFactory_R.h>
#include <l0-infra/array/mixin/min/ScopeViewMinElem.h>
#include <l0-infra/array/mixin/factory/ScopeSliceMaker.h>
#include <l0-infra/array/mixin/sort/ScopeViewSort.h>
#include <l0-infra/array/mixin/sort/BasicSort.h>
#include <l0-infra/array/mixin/sort/BasicSort_R.h>
#include <l0-infra/array/mixin/eq/ScopedArrayLikeEquality.h>
#include <l0-infra/array/mixin/factory/WithIndexScopeArrayLikeFactory.h>
#include <l0-infra/array/mixin/append/ViewAppend.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/replace/ViewReplace.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/eq/ObjectCompareExt.h>
#include <l0-infra/array/mixin/sort/SortExt_R.h>

namespace scope_view {
    using Private = ::mixin::Private<
            mixin::ScopedArrayLike,
            mixin::ViewedArray,
            mixin::ViewObjectLess,
            mixin::ViewObjectEquality,
            mixin::ObjectCompareExt,
            mixin::ViewedArrayRange,
            mixin::ArrayObjectAccessor,
            mixin::ScopeSimpleForEach,
            mixin::ScopeSliceMaker,
            mixin::___mutable_mixin_delimiter___,
            mixin::ScopeViewSort>;

    using Public = ::mixin::Public<
            mixin::RangeExporter,
            mixin::ByIndexRefAccessor,
            mixin::ScopedElemCount,
            mixin::ByIndexAccessor,
            mixin::IterableScopedArrayLike,
            mixin::WithIndexScopeArrayLikeFactory,
            mixin::WithIndexScopeArrayLikeFactory_R,
            mixin::SimpleForEachExt,
            mixin::ScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::ScopeViewMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopeMinElemsFactory,
            mixin::ScopeMinElemsFactory_R,
            mixin::ScopeSortViewFactory,
            mixin::ScopeSortViewFactory_R,
            mixin::ScopedArrayLikeEquality,
            mixin::___mutable_mixin_delimiter___,
            mixin::ViewAppend,
            mixin::AppendExt,
            mixin::ViewReplace,
            mixin::ReplaceExt,
            mixin::BasicSort,
            mixin::BasicSort_R,
            mixin::SortExt,
            mixin::SortExt_R>;

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
using ValueScopeView = scope_view::Array<typename holder::ScopeView<ARRAY>::ValueView>;

template<typename ARRAY>
struct RefScopeView : scope_view::Array<typename holder::ScopeView<ARRAY>::RefView> {
    using Parent = scope_view::Array<typename holder::ScopeView<ARRAY>::RefView>;
    using Parent::Parent;
};

#endif //OBJECT_ARRAY_2_AF881B1A6C05426D9E9034C73574A55C
