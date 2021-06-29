//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_RANGEDARRAYLIKE_H
#define OBJECT_ARRAY_RANGEDARRAYLIKE_H

#include <l0-infra/array/detail/config.h>
#include <l0-infra/array/concept/detail/ConceptDef.h>
#if HAS_CONCEPT
#include <l0-infra/array/concept/IndexedContainer.h>
#include <concepts>

namespace _concept {
    template<typename T>
    struct SimpleRangedArrayLikeChecker : T {
        using T::IndexBegin;
        using T::IndexEnd;
        using typename T::SizeType;
    };

    template<typename T>
    concept SimpleRangedArrayLike = IndexedContainer<T> &&
    requires(SimpleRangedArrayLikeChecker<T> const& o) {
        { o.IndexBegin() } -> std::same_as<typename SimpleRangedArrayLikeChecker<T>::SizeType>;
        { o.IndexEnd() } -> std::same_as<typename SimpleRangedArrayLikeChecker<T>::SizeType>;
    };

    template<typename T>
    struct ConstRangedArrayLikeChecker : T {
        using T::ObjectBegin;
        using T::ObjectEnd;
        using typename T::ObjectType;
    };

    template<typename T>
    concept ConstRangedArrayLike = SimpleRangedArrayLike<T> &&
    requires(ConstRangedArrayLikeChecker<T> const& o) {
        { o.ObjectBegin() } -> std::same_as<typename ConstRangedArrayLikeChecker<T>::ObjectType const*>;
        { o.ObjectEnd() } -> std::same_as<typename ConstRangedArrayLikeChecker<T>::ObjectType const*>;
    };

    template<typename T>
    struct RangedArrayLikeChecker : T {
        using T::ObjectBegin;
        using T::ObjectEnd;
        using typename T::ObjectType;
    };

    template<typename T>
    concept RangedArrayLike = ConstRangedArrayLike<T> &&
    requires(RangedArrayLikeChecker<std::decay_t<T>>& o) {
       { o.ObjectBegin() } -> std::same_as<typename RangedArrayLikeChecker<std::decay_t<T>>::ObjectType*>;
       { o.ObjectEnd() } -> std::same_as<typename RangedArrayLikeChecker<std::decay_t<T>>::ObjectType*>;
    };
}
#endif

#endif //OBJECT_ARRAY_RANGEDARRAYLIKE_H
