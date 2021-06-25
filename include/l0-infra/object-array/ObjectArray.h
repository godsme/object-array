//
// Created by Darwin Yuan on 2021/6/22.
//

#ifndef OBJECT_ARRAY_OBJECTARRAY_H
#define OBJECT_ARRAY_OBJECTARRAY_H

#include <l0-infra/object-array/holder/ObjectArrayDataHolder.h>
#include <l0-infra/object-array/detail/ContinuousArrayMixin.h>
#include <l0-infra/object-array/detail/ContinuousArrayLike.h>

namespace detail {
    using ObjectArrayMixins =
            detail::ContinuousArrayMixin::Extends<
                mixin::RangedViewFactory,
                mixin::ScopedViewFactory,
                mixin::IndexedViewFactory>;

    template<typename T, std::size_t MAX_NUM, bool ORDERED>
    using ObjectArray = detail::ContinuousArrayLike<
            holder::ObjectArrayDataHolder<T, MAX_NUM>,
            ObjectArrayMixins,
            ORDERED>;
}

template<typename T, std::size_t MAX_NUM, bool ORDERED = false>
using ObjectArray = detail::ObjectArray<T, MAX_NUM, ORDERED>;

#endif //OBJECT_ARRAY_OBJECTARRAY_H
