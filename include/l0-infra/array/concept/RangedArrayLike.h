//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_RANGEDARRAYLIKE_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/IndexedContainer.h>
#include <concepts>

namespace _concept::detail {
    template<typename T>
    struct SimpleRangedArrayLikeChecker : T {
        using T::IndexBegin;
        using T::IndexEnd;
        using typename T::SizeType;
    };

    template<typename T>
    concept SimpleRangedArrayLike_ = requires(T const& o) {
        { o.IndexBegin() } -> std::same_as<typename T::SizeType>;
        { o.IndexEnd() } -> std::same_as<typename T::SizeType>;
    };

    template<typename T>
    concept SimpleRangedArrayLike = SimpleRangedArrayLike_<SimpleRangedArrayLikeChecker<T>>;
}

namespace _concept {
    template<typename T>
    concept SimpleRangedArrayLike = IndexedContainer<T> && detail::SimpleRangedArrayLike<T>;
}

//namespace _concept::detail {
//    template<typename T>
//    struct ConstRangedArrayLikeChecker : T {
//        using T::ObjectBegin;
//        using T::ObjectEnd;
//        using typename T::ObjectType;
//    };
//
//    template<typename T>
//    concept ConstRangedArrayLike_ = requires(T const& o) {
//        { o.ObjectBegin() } -> std::same_as<typename T::ObjectType const*>;
//        { o.ObjectEnd() } -> std::same_as<typename T::ObjectType const*>;
//    };
//
//    template<typename T>
//    concept ConstRangedArrayLike = ConstRangedArrayLike_<ConstRangedArrayLikeChecker<T>>;
//}
//
//namespace _concept {
//    template<typename T>
//    concept ConstRangedArrayLike = SimpleRangedArrayLike<T> && detail::ConstRangedArrayLike<T>;
//}
//
//namespace _concept::detail {
//    template<typename T>
//    struct RangedArrayLikeChecker : T {
//        using T::ObjectBegin;
//        using T::ObjectEnd;
//        using typename T::ObjectType;
//    };
//
//    template<typename T>
//    concept RangedArrayLike_ = requires(T& o) {
//        { o.ObjectBegin() } -> std::same_as<typename T::ObjectType*>;
//        { o.ObjectEnd() } -> std::same_as<typename T::ObjectType*>;
//    };
//
//    template<typename T>
//    concept RangedArrayLike = RangedArrayLike_<RangedArrayLikeChecker<std::decay_t<T>>>;
//}
//
//namespace _concept {
//    template<typename T>
//    concept RangedArrayLike = ConstRangedArrayLike<T> && detail::RangedArrayLike<T>;
//}

#endif

#endif //OBJECT_ARRAY_RANGEDARRAYLIKE_H
