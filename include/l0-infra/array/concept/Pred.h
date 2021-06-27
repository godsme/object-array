//
// Created by Darwin Yuan on 2021/6/20.
//

#ifndef OBJECT_ARRAY_PRED_H
#define OBJECT_ARRAY_PRED_H

#include <l0-infra/array/detail/config.h>
#if HAS_CONCEPT
#include <concepts>
#include <type_traits>

namespace _concept {
    template<typename PRED, typename ELEM>
    concept SimplePred = requires(PRED&& pred, ELEM const& elem) {
        { pred(elem) } -> std::same_as<bool>;
    };

    template<typename PRED, typename ELEM, typename SizeType>
    concept WithIndexPred = requires(PRED&& pred, ELEM const& elem, SizeType n) {
        { pred(elem, n) } -> std::same_as<bool>;
    };

    template<typename PRED, typename ELEM, typename SizeType>
    concept Pred = WithIndexPred<PRED, ELEM, SizeType> || SimplePred<PRED, ELEM>;
}
#endif

#endif //OBJECT_ARRAY_PRED_H
