//
// Created by Darwin Yuan on 2021/6/26.
//

#ifndef OBJECT_ARRAY_ARRAYINDICES_H
#define OBJECT_ARRAY_ARRAYINDICES_H

#include <l0-infra/array/holder/ArrayIndicesDataHolder.h>
#include <l0-infra/array/detail/ContinuousArrayMixin.h>

namespace detail {
    using ArrayIndicesMixins = ContinousReadOnlyMixins;

    template<std::size_t MAX_NUM>
    using ArrayIndices = SimpleReadOnlyArrayLike<holder::ArrayIndicesDataHolder<MAX_NUM>, ArrayIndicesMixins, true>;
}

template<std::size_t MAX_NUM>
class ArrayIndices : public detail::ArrayIndices<MAX_NUM> {
    using Parent = detail::ArrayIndices<MAX_NUM>;
    using typename Parent::Mixins;
    using typename Parent::Holder;

public:
    using Parent::Parent;
    using Holder::InitWith;
};

#endif //OBJECT_ARRAY_ARRAYINDICES_H
