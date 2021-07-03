//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTIGUOUSARRAYLIKEDATAHOLDER_H
#define OBJECT_ARRAY_CONTIGUOUSARRAYLIKEDATAHOLDER_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT

#include <l0-infra/array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept::detail {
    template<typename T>
    struct WithNumberChecker : T {
        using T::Num;
        using typename T::SizeType;
    };

    template<typename T>
    concept ConstWithNumber_ = requires(T const& o) {
        { o.Num() } -> std::same_as<typename T::SizeType>;
    };

    template<typename T>
    concept ConstWithNumber = ConstWithNumber_<WithNumberChecker<T>>;
}

namespace _concept {
    template<typename T>
    concept ConstContiguousArrayLikeDataHolder = SimpleArrayLike<T> && detail::ConstWithNumber<T>;
}

namespace _concept::detail {
    template<typename T>
    concept WithNumber_ = requires(T & o) {
        { o.Num() } -> std::same_as<typename T::SizeType&>;
    };

    template<typename T>
    concept WithNumber = WithNumber_<WithNumberChecker<T>>;
}

namespace _concept {
    template<typename T>
    concept ContiguousArrayLikeDataHolder = ConstContiguousArrayLikeDataHolder<T> && detail::WithNumber<T>;
}

#endif

#endif //OBJECT_ARRAY_CONTIGUOUSARRAYLIKEDATAHOLDER_H
