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

    template<typename BASE, bool C, template<typename> typename ... MIXINS>
    struct CombineMutableMixins {
        using Type = BASE;
    };

    template<typename BASE, template<typename> typename ... MIXINS>
    struct CombineMutableMixins<BASE, false, MIXINS...> {
        using Type = typename CombineMixin<MIXINS...>::template Type<BASE>;;
    };

    template<typename BASE, bool C, template<typename> typename H, template<typename> typename ... MIXINS>
    struct DoCombineMixins {
        using Type = typename CombineMutableMixins<BASE, H<BASE>::IS_CONST, MIXINS...>::Type;
    };

    template<typename BASE, template<typename> typename H, template<typename> typename ... MIXINS>
    struct DoCombineMixins<BASE, false, H, MIXINS...> {
        using Type = typename CombineMixin<MIXINS...>::template Type<H<BASE>>;
    };

    template<template<typename> typename H, template<typename> typename ... MIXINS>
    struct CombineMixin<H, MIXINS...> {
        template<typename BASE>
        using Type = typename DoCombineMixins<BASE, std::is_final_v<H<BASE>>, H, MIXINS...>::Type;
    };

    template<typename OWNER, typename T>
    struct DataHolderInterface : T::Interface {
        using DataHolder = T;
        using Owner = OWNER;
        using SizeType = typename DataHolder::SizeType;
        constexpr static SizeType MAX_SIZE = DataHolder::MAX_SIZE;
        constexpr static bool ORDERED = T::IS_ORDERED;
        constexpr static bool CONST = T::IS_CONST;
        using BitMap = ::detail::ArrayScope<MAX_SIZE>;
        using Maybe = ::detail::DeduceIntOptional_t<MAX_SIZE>;

        using OffsetType = ::detail::ArrayOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;
    };
}

namespace mixin {
    template<template<typename> typename ... MIXINS>
    struct Mixins {
        template<typename HOLDER>
        struct Compose : HOLDER, detail::CombineMixin<MIXINS...>::template Type<detail::DataHolderInterface<Compose<HOLDER>, HOLDER>> {
        public:
            using Holder = HOLDER;
            using Mixins = typename detail::CombineMixin<MIXINS...>::template Type<detail::DataHolderInterface<Compose<HOLDER>, HOLDER>>;

        private:
            static auto __sEcReAtE_vAliD_cHeCkEr() { static_assert(sizeof(HOLDER) == sizeof(Compose)); }
            static_assert(std::is_empty_v<Mixins>);

        public:
            using Holder::Holder;
            using typename Mixins::SizeType;
            using typename Mixins::ObjectType;
            using typename Mixins::BitMap;
            using typename Mixins::Maybe;
        };

        template<typename T>
        using Mixin = typename detail::CombineMixin<MIXINS...>::template Type<T>;

        template<template<typename> typename ... MORE_MIXINS>
        using Extends = Mixins<MIXINS..., MORE_MIXINS...>;

        template<typename LHS>
        using Prepend = typename LHS::template Extends<MIXINS...>;

        template<typename RHS>
        using Concat = typename RHS::template Prepend<Mixins<MIXINS...>>;
    };
}

#endif //OBJECT_ARRAY_MIXINS_H
