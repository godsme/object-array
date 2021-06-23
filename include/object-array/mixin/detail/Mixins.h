//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_MIXINS_H
#define OBJECT_ARRAY_MIXINS_H

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
}

namespace mixin {
    template<template<typename> typename ... MIXINS>
    struct Mixins {
        template<typename HOLDER>
        using Type = typename detail::CombineMixin<MIXINS...>::template Type<HOLDER>;

        template<template<typename> typename ... MORE_MIXINS>
        using Extends = Mixins<MIXINS..., MORE_MIXINS...>;
    };
}

#endif //OBJECT_ARRAY_MIXINS_H
