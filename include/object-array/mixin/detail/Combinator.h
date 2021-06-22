//
// Created by Darwin Yuan on 2021/6/21.
//

#ifndef OBJECT_ARRAY_COMBINATOR_H
#define OBJECT_ARRAY_COMBINATOR_H

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
    template<typename HOLDER, template<typename> typename ... MIXINS>
    struct Combinator : protected HOLDER, protected detail::CombineMixin<MIXINS...>::template Type<HOLDER> {
    private:
        static auto __sEcReAtE_vAliD_cHeCkEr() { static_assert(sizeof(HOLDER) == sizeof(Combinator)); }
    public:
        using Holder = HOLDER;
        using Mixins = typename detail::CombineMixin<MIXINS...>::template Type<HOLDER>;
        using Holder::Holder;

        using SizeType = typename Holder::SizeType;
        using ObjectType = typename Holder::ObjectType;

        static_assert(std::is_empty_v<Mixins>);
    };
}

#endif //OBJECT_ARRAY_COMBINATOR_H
