//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H

#include <l0-infra/array/detail/config.h>
#include <l0-infra/array/concept/detail/ConceptDef.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept {
    template<typename T>
    concept ConstContinuousArrayLikeDataHolder = SimpleArrayLike<T> &&
    requires(T const& o) {
        { o.Num() } -> std::same_as<typename T::SizeType>;
    };

    template<typename T>
    concept ContinuousArrayLikeDataHolder = ConstContinuousArrayLikeDataHolder<T> &&
    requires(T& o) {
        { o.Num() } -> std::same_as<typename T::SizeType&>;
    };
}
#endif

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H
