//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_SCATTEREDARRAY_H
#define OBJECT_ARRAY_2_SCATTEREDARRAY_H

#include <l0-infra/array/holder/ScatteredArrayHolder.h>
#include <l0-infra/array/mixin/detail/Mixins.h>
#include <l0-infra/array/mixin/array_like/ConstArrayLike.h>
#include <l0-infra/array/mixin/array_like/ConstScatteredArrayLike.h>
#include <l0-infra/array/mixin/detail/___mutable_mixin_delimiter___.h>
#include <l0-infra/array/mixin/array_like/ArrayLike.h>
#include <l0-infra/array/mixin/array_like/ScatteredArrayLike.h>
#include <l0-infra/array/mixin/access/ByIndexRefAccessor.h>
#include <l0-infra/array/mixin/find/UnsafeRangeFind.h>
#include <l0-infra/array/mixin/find/UnsafeScopedRangeFind.h>
#include <l0-infra/array/mixin/find/ScatteredArrayFind.h>
#include <l0-infra/array/mixin/find/SimpleFindExt.h>
#include <l0-infra/array/mixin/sort/UnsafeRangeScopeSort.h>
#include <l0-infra/array/mixin/factory/ScatteredArraySliceMaker.h>
#include <l0-infra/array/mixin/sort/ScatteredArraySort.h>
#include <l0-infra/array/mixin/foreach/ScatteredArrayForEach.h>
#include <l0-infra/array/mixin/factory/WithIndexScopeArrayLikeFactory.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/append/AppendExt.h>
#include <l0-infra/array/mixin/min/ScatteredArrayMinElem.h>
#include <l0-infra/array/mixin/replace/ReplaceExt.h>
#include <l0-infra/array/mixin/less/ObjectLess.h>
#include <l0-infra/array/mixin/eq/ObjectEquality.h>
#include <l0-infra/array/mixin/erase/ClearExporter.h>
#include <l0-infra/array/mixin/count/FullScopeElemCount.h>

namespace holder::detail {
    template<typename, std::size_t>
    struct IndexedArrayHolder;
}

namespace scattered_array {
    using Private = ::mixin::Private<
            mixin::ObjectLess,
            mixin::ObjectEquality,
            mixin::ObjectCompareExt,

            mixin::ConstArrayLike,
            mixin::ConstScatteredArrayLike,

            mixin::UnsafeRangeFind,
            mixin::UnsafeScopedRangeFind,
            mixin::ArrayElemVisit,
            mixin::UnsafeRangeScopeForEach,
            mixin::ScatteredArrayForEach,
            mixin::UnsafeRangeScopeMinElem,
            mixin::ScatteredArraySliceMaker,
            mixin::___mutable_mixin_delimiter___,
            mixin::ArrayLike,
            mixin::ScatteredArrayLike,
            mixin::UnsafeRangeScopeSort,
            mixin::ScatteredArraySort>;

    using Public = ::mixin::Public<
            mixin::ObjectIndex,
            mixin::RangeExporter,
            mixin::ByIndexRefAccessor,
            mixin::ScopedElemCount,
            mixin::FullScopedElemCount,
            mixin::ByIndexAccessor,
            mixin::ScatteredArrayFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::ScatteredArrayMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedArrayLikeEquality,
            mixin::ScopeSortViewFactory,
            mixin::IterableScopedArrayLike,
            mixin::WithIndexScopeArrayLikeFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::AppendExt,
            mixin::ReplaceExt,
            mixin::EraseExt,
            mixin::ClearExporter,
            mixin::BasicSort,
            mixin::SortExt>;

    template<typename HOLDER>
    struct Array : Public::Compose<HOLDER, Private, Array<HOLDER>> {
        using Parent = Public::Compose<HOLDER, Private, Array<HOLDER>>;
        using Parent::Parent;
        Array() {}

        using Parent::GetScope;

    private:
        template<typename>
        friend class mixin::ViewObjectLess;

        template<typename>
        friend class mixin::ViewObjectEquality;

        template<typename, std::size_t>
        friend struct holder::detail::IndexedArrayHolder;
    };
}

template<typename OBJ, std::size_t MAX_NUM>
using ScatteredArray = scattered_array::Array<holder::ScatteredArrayHolder<OBJ, MAX_NUM>>;

#endif //OBJECT_ARRAY_2_SCATTEREDARRAY_H
