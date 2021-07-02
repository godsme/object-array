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

namespace _concept::detail {
    template<typename T>
    struct ElemVisitorChecker : T {
        using T::Visit;
        using typename T::SizeType;
    };

    template<typename T>
    concept ElemVisitor_ = requires(T const &o, typename T::SizeType n, typename detail::OpTypeTrait<T> &&trait) {
        { o.template Visit<false>(trait.CONST_PRED, n) } -> std::same_as<void>;
        { o.template Visit<false>(trait.CONST_INDEX_PRED, n) } -> std::same_as<void>;
        { o.template Visit<true>(trait.PRED, n) } -> std::same_as<void>;
        { o.template Visit<true>(trait.INDEX_PRED, n) } -> std::same_as<void>;

        { o.template Visit<false>(trait.BOOL_CONST_PRED, n) } -> std::same_as<bool>;
        { o.template Visit<false>(trait.BOOL_CONST_INDEX_PRED, n) } -> std::same_as<bool>;
        { o.template Visit<true>(trait.BOOL_INDEX_PRED, n) } -> std::same_as<bool>;
        { o.template Visit<true>(trait.BOOL_PRED, n) } -> std::same_as<bool>;

        { o.template Visit<false>(trait.STATUS_CONST_PRED, n) } -> std::same_as<unsigned int>;
        { o.template Visit<false>(trait.STATUS_CONST_INDEX_PRED, n) } -> std::same_as<unsigned int>;
        { o.template Visit<true>(trait.STATUS_INDEX_PRED, n) } -> std::same_as<unsigned int>;
        { o.template Visit<true>(trait.STATUS_PRED, n) } -> std::same_as<unsigned int>;
    };
}

namespace _concept {
    template<typename T>
    concept ElemVisitor = detail::ElemVisitor_<detail::ElemVisitorChecker<T>>;

    template<typename T>
    concept OpVisitable = SimpleRangedArrayLike<T> && ElemVisitor<T>;
}

#endif

#endif //OBJECT_ARRAY_ELEMVISITOR_H
