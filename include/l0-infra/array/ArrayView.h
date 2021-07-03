//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYVIEW_H
#define OBJECT_ARRAY_ARRAYVIEW_H

#include <l0-infra/array/holder/ConstArrayViewDataHolder.h>
#include <l0-infra/array/holder/ArrayViewDataHolder.h>
#include <l0-infra/array/mixin/factory/RValueRangedViewFactory.h>
#include <l0-infra/array/mixin/factory/SortViewFactory.h>
#include <l0-infra/array/mixin/erase/SimpleMutate.h>
#include <l0-infra/array/mixin/erase/EraseExt.h>
#include <l0-infra/array/mixin/erase/ScopedCleanUp.h>
#include <l0-infra/array/mixin/erase/SimpleErase.h>

namespace detail {
    using ArrayViewMixins = ::mixin::Mixins<
            mixin::ContinuousArrayLike,
            mixin::RangedArray,
            mixin::RangedArrayLike,
            mixin::ObjectIndex,
            mixin::ArrayElemVisit,
            mixin::ScopedFind,
            mixin::SimpleForEach,
            mixin::ScopedForEach,
            mixin::___public_mixin_delimiter___,
            mixin::IndexedRefAccessor,
            mixin::ByIndexAccessor,
            mixin::RangedElemCount,
            mixin::IterableArrayLike,
            mixin::NonScopedSimpleFind,
            mixin::SimpleFindExt,
            mixin::SimpleForEachExt,
            mixin::ScopedFindExt,
            mixin::ScopedForEachExt,
            mixin::SimpleMinElem,
            mixin::SimpleMinElemExt,
            mixin::ScopedMinElemExt,
            mixin::RValueRangedViewFactory,
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory,
            mixin::RValueSortViewFactory,
            mixin::___mutable_mixin_delimiter___,
            mixin::SimpleErase,
            mixin::SimpleMutate,
            mixin::ReplaceExt,
            mixin::AppendExt,
            mixin::EraseExt,
            mixin::ScopedCleanUp,
            mixin::RangedClear,
            mixin::RValueArraySort,
            mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM, typename ELEM, bool ORDERED>
    using ConstArrayView = ArrayViewMixins::Compose<holder::ConstArrayViewDataHolder<T, MAX_NUM, ELEM, ORDERED>>;
}

namespace detail {
    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename WRAPPER, bool ORDERED, bool = std::is_const_v<T>>
    struct ArrayViewTrait {
        using Type = ConstArrayView<T, MAX_NUM, WRAPPER, ORDERED>;
    };

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename WRAPPER, bool ORDERED>
    struct ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, WRAPPER, ORDERED, false> {
        using Type = ArrayViewMixins::Compose<holder::ArrayViewDataHolder<T, SIZE_TYPE, MAX_NUM, WRAPPER, ORDERED>>;
    };
}

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = T, bool ORDERED = false, typename Parent = typename detail::ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, ELEM, ORDERED>::Type>
struct ArrayView  : Parent {
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ArrayView(T (&)[MAX_NUM], SIZE_TYPE& size) -> ArrayView<T, SIZE_TYPE, MAX_NUM, T, false>;

template<typename T, std::size_t MAX_NUM, typename WRAPPER = T, bool ORDERED = false, typename Parent = detail::ConstArrayView<T, MAX_NUM, WRAPPER, ORDERED>>
struct ConstArrayView : Parent {
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ConstArrayView(T const (&)[MAX_NUM], SIZE_TYPE) -> ConstArrayView<T, MAX_NUM, T>;

#endif //OBJECT_ARRAY_ARRAYVIEW_H
