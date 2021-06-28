//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYVIEW_H
#define OBJECT_ARRAY_ARRAYVIEW_H

#include <l0-infra/array/holder/ConstArrayViewDataHolder.h>
#include <l0-infra/array/holder/ArrayViewDataHolder.h>
#include <l0-infra/array/detail/ContinuousArrayMixin.h>
#include <l0-infra/array/mixin/RValueRangedViewFactory.h>
#include <l0-infra/array/mixin/SortViewFactory.h>

namespace detail {
    using ArrayViewSpecifiedMixins = ::mixin::Mixins<
            mixin::RValueRangedViewFactory,
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory,
            mixin::RValueSortViewFactory>;

    using ConstArrayViewMixins = detail::ContinousReadOnlyMixins::Concat<ArrayViewSpecifiedMixins>;
    using ArrayViewMixins = detail::ContinuousArrayMixin::Concat<ArrayViewSpecifiedMixins>
            ::Extends<mixin::RValueArraySort, mixin::ArraySortExt>;

    template<typename T, std::size_t MAX_NUM, typename ELEM, bool ORDERED>
    using ConstArrayView = ConstArrayViewMixins::Compose<holder::ConstArrayViewDataHolder<T, MAX_NUM, ELEM, ORDERED>>;

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename WRAPPER, bool ORDERED, bool = std::is_const_v<T>>
    struct ArrayViewTrait {
        using Type = ConstArrayView<T, MAX_NUM, WRAPPER, ORDERED>;
    };

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename WRAPPER, bool ORDERED>
    struct ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, WRAPPER, ORDERED, false> {
        using Type = ArrayViewMixins::Compose<holder::ArrayViewDataHolder<T, SIZE_TYPE, MAX_NUM, WRAPPER, ORDERED>>;
    };
}

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = T, bool ORDERED = false>
class ArrayView : public detail::ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, ELEM, ORDERED>::Type {
    using Parent = typename detail::ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, ELEM, ORDERED>::Type;
    using typename Parent::Holder;
public:
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ArrayView(T (&)[MAX_NUM], SIZE_TYPE& size) -> ArrayView<T, SIZE_TYPE, MAX_NUM, T, false>;

template<typename T, std::size_t MAX_NUM, typename WRAPPER = T, bool ORDERED = false>
struct ConstArrayView : detail::ConstArrayView<T, MAX_NUM, WRAPPER, ORDERED> {
    using Parent = detail::ConstArrayView<T, MAX_NUM, WRAPPER, ORDERED>;
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ConstArrayView(T const (&)[MAX_NUM], SIZE_TYPE) -> ConstArrayView<T, MAX_NUM, T>;

#endif //OBJECT_ARRAY_ARRAYVIEW_H
