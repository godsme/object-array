//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <l0-infra/array/holder/ObjectArrayDataHolder.h>
#include <l0-infra/array/detail/ContinuousArrayMixin.h>
#include <l0-infra/array/detail/ContinuousArrayLike.h>
#include <l0-infra/array/mixin/SortViewFactory.h>

namespace detail {
    using ObjectArrayMixins = detail::ContinuousArrayMixin::Extends<
                mixin::RangedViewFactory,
                mixin::ScopedViewFactory,
                mixin::IndexedViewFactory,
                mixin::SortViewFactory,
                mixin::ArraySort,
                mixin::ArraySortExt>;

//    template<typename T, std::size_t MAX_NUM, typename OWNER, bool ORDERED>
//    using ObjectArray = detail::ContinuousArrayLike<
//            holder::ObjectArrayDataHolder<T, MAX_NUM, OWNER>,
//            ObjectArrayMixins,
//            ORDERED>;

    template<typename T, std::size_t MAX_NUM>
    using ObjectArray = typename holder::ObjectArrayDataHolder<T, MAX_NUM, detail::ObjectArrayMixins>;
}

template<typename T, std::size_t MAX_NUM>
using ObjectArray = detail::ObjectArray<T, MAX_NUM>;

#endif //OBJECT_ARRAY_OBJECTARRAY_H
