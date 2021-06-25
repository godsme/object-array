//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_MIXINS_H
#define OBJECT_ARRAY_MIXINS_H

#include <l0-infra/base/DeduceOffsetType.h>
#include <l0-infra/base/BitSet.h>
#include <l0-infra/base/detail/DeduceIntOptional.h>
#include <object-array/ArrayOffset.h>
#include <object-array/detail/ArrayScope.h>
#include <type_traits>

namespace mixin::detail {
    template<template<typename> typename ... MIXINS>
    struct CombineMixin {
        template<typename BASE>
        using Type = BASE;
    };

    template<template<typename> typename H, template<typename> typename ... MIXINS>
    struct CombineMixin<H, MIXINS...> {
        template<typename BASE>
        using Type = typename CombineMixin<MIXINS...>::template Type<H<BASE>>;
    };

    template<typename T>
    struct DataHolderInterface : T::Interface {
        using DataHolder = T;
        using SizeType = typename T::SizeType;
        constexpr static SizeType MAX_SIZE = T::MAX_SIZE;
        using BitMap = ::detail::ArrayScope<MAX_SIZE>;
        using Maybe = ::detail::DeduceIntOptional_t<MAX_SIZE>;
        using OffsetType = ArrayOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
        using EndOffsetType = ArrayEndOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
    };
}

namespace mixin {
    template<template<typename> typename ... MIXINS>
    struct Mixins {
        template<typename HOLDER>
        using Type = typename detail::CombineMixin<MIXINS...>::template Type<detail::DataHolderInterface<HOLDER>>;

        template<template<typename> typename ... MORE_MIXINS>
        using Extends = Mixins<MIXINS..., MORE_MIXINS...>;

        template<typename LHS>
        using Prepend = typename LHS::template Extends<MIXINS...>;

        template<typename RHS>
        using Concat = typename RHS::template Prepend<Mixins<MIXINS...>>;
    };
}

#endif //OBJECT_ARRAY_MIXINS_H
