//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H
#define OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/SimpleArrayLike.h>
#include <concepts>

namespace _concept {
    namespace detail {
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

    template<typename T>
    concept ConstContinuousArrayLikeDataHolder = SimpleArrayLike<T> && detail::ConstWithNumber<T>;

    namespace detail {
        template<typename T>
        concept WithNumber_ = requires(T & o) {
            { o.Num() } -> std::same_as<typename T::SizeType&>;
        };

        template<typename T>
        concept WithNumber = WithNumber_<WithNumberChecker<T>>;
    }

    template<typename T>
    concept ContinuousArrayLikeDataHolder = ConstContinuousArrayLikeDataHolder<T> && detail::WithNumber<T>;
}

#endif

#endif //OBJECT_ARRAY_CONTINUOUSARRAYLIKEDATAHOLDER_H
