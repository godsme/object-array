//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_ARRAYVIEW_H
#define OBJECT_ARRAY_ARRAYVIEW_H

#include <l0-infra/array/holder/ConstArrayViewDataHolder.h>
#include <l0-infra/array/holder/ArrayViewDataHolder.h>
#include <l0-infra/array/detail/ContinuousArrayMixin.h>
#include <l0-infra/array/detail/ArrayComposer.h>
#include <l0-infra/array/mixin/RValueRangedViewFactory.h>
#include <l0-infra/array/detail/ContinuousArrayLike.h>
#include <l0-infra/array/detail/ContinuousReadOnlyArray.h>
#include <l0-infra/array/mixin/SortViewFactory.h>

namespace detail {
    using ArrayViewSpecifiedMixins = ::mixin::Mixins<
            mixin::RValueRangedViewFactory,
            mixin::RValueScopedViewFactory,
            mixin::RValueIndexedViewFactory,
            mixin::SortViewFactory>;

    using ConstArrayViewMixins = detail::ContinousReadOnlyMixins::Concat<ArrayViewSpecifiedMixins>;
    using ArrayViewMixins = detail::ContinuousArrayMixin::Concat<ArrayViewSpecifiedMixins>;

    template<typename T, std::size_t MAX_NUM, typename OWNER, typename ELEM, bool ORDERED>
    using ConstArrayView = detail::ContinuousReadOnlyArray<holder::ConstArrayViewDataHolder<T, MAX_NUM, OWNER, ELEM>, ConstArrayViewMixins, ORDERED>;

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename OWNER, typename WRAPPER, bool = std::is_const_v<T>>
    struct ArrayViewTrait {
        using Type = ConstArrayView<T, MAX_NUM, OWNER, WRAPPER, false>;
    };

    template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename OWNER, typename WRAPPER>
    struct ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, OWNER, WRAPPER, false> {
        using Type = detail::ContinuousArrayLike<holder::ArrayViewDataHolder<T, SIZE_TYPE, MAX_NUM, OWNER, WRAPPER>, ArrayViewMixins, false>;
    };
}

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM, typename ELEM = T>
class ArrayView : public detail::ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, ArrayView<T, SIZE_TYPE, MAX_NUM, ELEM>, ELEM>::Type {
    using Parent = typename detail::ArrayViewTrait<T, SIZE_TYPE, MAX_NUM, ArrayView<T, SIZE_TYPE, MAX_NUM, ELEM>, ELEM>::Type;
    using typename Parent::Holder;
public:
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ArrayView(T (&)[MAX_NUM], SIZE_TYPE& size) -> ArrayView<T, SIZE_TYPE, MAX_NUM>;

template<typename T, std::size_t MAX_NUM, typename WRAPPER = T>
struct ConstArrayView : detail::ConstArrayView<T, MAX_NUM, ConstArrayView<T, MAX_NUM, WRAPPER>, WRAPPER, false> {
    using Parent = detail::ConstArrayView<T, MAX_NUM, ConstArrayView<T, MAX_NUM, WRAPPER>, WRAPPER, false>;
    using Parent::Parent;
};

template<typename T, typename SIZE_TYPE, SIZE_TYPE MAX_NUM>
ConstArrayView(T const (&)[MAX_NUM], SIZE_TYPE) -> ConstArrayView<T, MAX_NUM, T>;

#endif //OBJECT_ARRAY_ARRAYVIEW_H