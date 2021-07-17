//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_9B8C37879D5347CF8EF6712A5A128345
#define OBJECT_ARRAY_9B8C37879D5347CF8EF6712A5A128345

#include <l0-infra/array/holder/FilterHolder.h>
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
#include <l0-infra/array/mixin/factory/ScopeEnumViewFactory.h>
#include <l0-infra/array/mixin/factory/ScopeEnumViewFactory_R.h>

namespace scope_view {
    using Private = ::mixin::Private<
            mixin::ViewedArray,
            mixin::ViewObjectLess,
            mixin::ViewObjectEquality,
            mixin::ObjectCompareExt,
            mixin::ViewedArrayRange,
            mixin::ArrayObjectAccessor,
            mixin::___mutable_mixin_delimiter___>;

    using Public = ::mixin::Public<
            mixin::RangeExporter,
            mixin::SimpleForEachExt,
            mixin::SimpleFindExt,
            mixin::SimpleMinElemExt,
            mixin::___mutable_mixin_delimiter___,
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

#endif //OBJECT_ARRAY_9B8C37879D5347CF8EF6712A5A128345
