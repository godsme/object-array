//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_MIXINS_H
#define OBJECT_ARRAY_MIXINS_H

#include <l0-infra/base/DeduceOffsetType.h>
#include <l0-infra/base/BitSet.h>
#include <l0-infra/base/detail/DeduceIntOptional.h>
#include <l0-infra/array/detail/ArrayOffset.h>
#include <l0-infra/array/detail/ArrayScope.h>
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
        using SizeType = typename DataHolder::SizeType;
        constexpr static SizeType MAX_SIZE = DataHolder::MAX_SIZE;
        using BitMap = ::detail::ArrayScope<MAX_SIZE>;
        using Maybe = ::detail::DeduceIntOptional_t<MAX_SIZE>;
        using OffsetType = ::detail::ArrayOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
    };

    template<typename OWNER, typename T>
    struct DataHolderInterface1 : T::Interface {
        using DataHolder = T;
        using Owner = OWNER;
        using SizeType = typename DataHolder::SizeType;
        constexpr static SizeType MAX_SIZE = DataHolder::MAX_SIZE;
        constexpr static bool ORDERED = T::ORDERED;
        using BitMap = ::detail::ArrayScope<MAX_SIZE>;
        using Maybe = ::detail::DeduceIntOptional_t<MAX_SIZE>;

        using OffsetType = ::detail::ArrayOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
    };
}

namespace mixin {
    template<template<typename> typename ... MIXINS>
    struct Mixins {
        template<typename HOLDER>
        using Type = typename detail::CombineMixin<MIXINS...>::template Type<detail::DataHolderInterface<HOLDER>>;

        template<typename HOLDER>
        struct Compose : HOLDER, detail::CombineMixin<MIXINS...>::template Type<detail::DataHolderInterface1<Compose<HOLDER>, HOLDER>> {
        public:
            using Holder = HOLDER;
            using Mixins = typename detail::CombineMixin<MIXINS...>::template Type<detail::DataHolderInterface1<Compose<HOLDER>, HOLDER>>;

        private:
            static auto __sEcReAtE_vAliD_cHeCkEr() { static_assert(sizeof(HOLDER) == sizeof(Compose)); }
            static_assert(std::is_empty_v<Mixins>);

        public:
            using HOLDER::HOLDER;
            using typename Mixins::SizeType;
            using typename Mixins::ObjectType;
            using typename Mixins::BitMap;
            using typename Mixins::Maybe;
        };

        template<template<typename> typename ... MORE_MIXINS>
        using Extends = Mixins<MIXINS..., MORE_MIXINS...>;

        template<typename LHS>
        using Prepend = typename LHS::template Extends<MIXINS...>;

        template<typename RHS>
        using Concat = typename RHS::template Prepend<Mixins<MIXINS...>>;
    };
}

#endif //OBJECT_ARRAY_MIXINS_H
