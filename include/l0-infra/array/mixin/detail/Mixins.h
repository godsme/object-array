//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_MIXINS_H
#define OBJECT_ARRAY_2_MIXINS_H

#include <l0-infra/base/DeduceOffsetType.h>
#include <l0-infra/base/BitSet.h>
#include <l0-infra/base/detail/DeduceIntOptional.h>
#include <l0-infra/array/detail/ArrayOffset.h>
#include <l0-infra/array/detail/ArrayScope.h>
#include <l0-infra/array/detail/CRTP.h>
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

    template<typename T, typename THIS_TYPE>
    struct DataHolderInfo {
        dEcL_tHiS(T);
        using ThisType = THIS_TYPE;
        using DataHolder = T;
        using ObjectType = typename DataHolder::ObjectType;
        using SizeType = typename DataHolder::SizeType;
        constexpr static SizeType MAX_SIZE = DataHolder::MAX_SIZE;
        constexpr static bool IS_ORDERED = T::IS_ORDERED;
        constexpr static bool IS_CONST = T::IS_CONST;
        using BitMap = ::detail::ArrayScope<MAX_SIZE>;
        using Maybe = ::detail::DeduceIntOpt_t<MAX_SIZE>;
        using OffsetType = ::detail::ArrayOffset<DeduceOffsetType_t<MAX_SIZE>, SizeType>;

        auto ToThisType() -> ThisType& { return reinterpret_cast<ThisType&>(*this); }
        auto ToThisType() const -> ThisType const& { return reinterpret_cast<ThisType const&>(*this); }
    };

    template<typename PRIVATE>
    struct ___public_mixin_delimiter___ : protected PRIVATE {};
}

namespace mixin {
    template<template<typename> typename ... MIXINS>
    struct Private {
        template<typename HOLDER, typename OWNER>
        using Type = typename detail::CombineMixin<MIXINS...>::template Type<detail::DataHolderInfo<HOLDER, OWNER>>;
    };

    template<template<typename> typename ... MIXINS>
    class Public {
        template<typename HOLDER, typename PRIVATE, typename OWNER>
        using AllMixins = typename detail::CombineMixin<MIXINS...>::template Type<detail::___public_mixin_delimiter___<typename PRIVATE::template Type<HOLDER, OWNER>>>;

    public:
        template<typename HOLDER, typename PRIVATE, typename OWNER>
        struct Compose : HOLDER, AllMixins<HOLDER, PRIVATE, OWNER> {
        public:
            using Holder = HOLDER;
            using Mixins = AllMixins<HOLDER, PRIVATE, OWNER>;

        private:
            static auto __sEcReAtE_vAliD_cHeCkEr() { static_assert(sizeof(HOLDER) == sizeof(Compose)); }
            static_assert(std::is_empty_v<Mixins>);

        public:
            using Holder::Holder;
            using typename Mixins::SizeType;
            using typename Mixins::ObjectType;
            using typename Mixins::BitMap;
            using typename Mixins::Maybe;

            constexpr static auto MAX_SIZE = Mixins::MAX_SIZE;
            constexpr static auto IS_CONST = Mixins::IS_CONST;
            constexpr static auto IS_ORDERED = Mixins::IS_ORDERED;
        };
    };
}

#endif //OBJECT_ARRAY_2_MIXINS_H
