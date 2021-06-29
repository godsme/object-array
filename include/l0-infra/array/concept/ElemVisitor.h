//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_ELEMVISITOR_H
#define OBJECT_ARRAY_ELEMVISITOR_H

#include <l0-infra/array/detail/config.h>

#if HAS_CONCEPT
#include <l0-infra/array/concept/detail/OpTypeTrait.h>
#include <l0-infra/array/concept/RangedArrayLike.h>
#include <concepts>
#include <type_traits>

namespace _concept {
    namespace detail {
        template<typename T>
        struct ElemVisitorChecker : T {
            using T::Visit;
            using typename T::SizeType;
        };

        template<typename T>
        concept ElemVisitor_ = requires(T const& o, typename T::SizeType n) {
            { o.template Visit<false>(std::declval<typename detail::OpTypeTrait<T>::ConstPredType&&>(), n) } -> std::same_as<void>;
            { o.template Visit<false>(std::declval<typename detail::OpTypeTrait<T>::ConstIndexPredType&&>(), n) } -> std::same_as<void>;
            { o.template Visit<true>(std::declval<typename detail::OpTypeTrait<T>::PredType&&>(), n) } -> std::same_as<void>;
            { o.template Visit<true>(std::declval<typename detail::OpTypeTrait<T>::IndexPredType&&>(), n) } -> std::same_as<void>;

            { o.template Visit<false>(std::declval<typename detail::OpTypeTrait<T>::BoolConstPredType&&>(), n) } -> std::same_as<bool>;
            { o.template Visit<false>(std::declval<typename detail::OpTypeTrait<T>::BoolConstIndexPredType&&>(), n) } -> std::same_as<bool>;
            { o.template Visit<true>(std::declval<typename detail::OpTypeTrait<T>::BoolPredType&&>(), n) } -> std::same_as<bool>;
            { o.template Visit<true>(std::declval<typename detail::OpTypeTrait<T>::BoolIndexPredType&&>(), n) } -> std::same_as<bool>;

            { o.template Visit<false>(std::declval<typename detail::OpTypeTrait<T>::StatusConstPredType&&>(), n) } -> std::same_as<unsigned int>;
            { o.template Visit<false>(std::declval<typename detail::OpTypeTrait<T>::StatusConstIndexPredType&&>(), n) } -> std::same_as<unsigned int>;
            { o.template Visit<true>(std::declval<typename detail::OpTypeTrait<T>::StatusPredType&&>(), n) } -> std::same_as<unsigned int>;
            { o.template Visit<true>(std::declval<typename detail::OpTypeTrait<T>::StatusIndexPredType&&>(), n) } -> std::same_as<unsigned int>;
        };
    }

    template<typename T>
    concept ElemVisitor = detail::ElemVisitor_<detail::ElemVisitorChecker<T>>;

    template<typename T>
    concept OpVisitable = SimpleRangedArrayLike<T> && ElemVisitor<T>;
}

#endif

#endif //OBJECT_ARRAY_ELEMVISITOR_H
