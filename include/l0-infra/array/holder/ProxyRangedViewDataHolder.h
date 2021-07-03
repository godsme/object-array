//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_PROXYRANGEDVIEWDATAHOLDER_H
#define OBJECT_ARRAY_PROXYRANGEDVIEWDATAHOLDER_H

#include <l0-infra/array/concept/RangedArrayLike.h>
#include <l0-infra/array/holder/detail/RangedViewDataHolderInterface.h>
#include <l0-infra/array/holder/detail/ArrayLikeViewDataHolder.h>
#include <l0-infra/array/holder/detail/ScopedViewDataHolderInterface.h>

namespace holder {
    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, typename SUB_TYPE, bool ORDERED>
    class ProxyRangedViewDataHolder {
    protected:
        dEcL_tHiS(SUB_TYPE);
        constexpr static auto CONST = std::is_const_v<std::remove_reference_t<ARRAY>>;
        using ArrayType = std::decay_t<ARRAY>;
    public:
        using ObjectType = std::conditional_t<CONST, std::add_const_t<typename ArrayType::ObjectType>, typename ArrayType::ObjectType>;
        using SizeType   = typename ArrayType::SizeType;

        constexpr static SizeType MAX_SIZE = ArrayType::MAX_SIZE;
        constexpr static bool IS_ORDERED = ORDERED;

        using Interface = detail::RangedViewDataHolderInterface<ProxyRangedViewDataHolder>;

    private:
        template<typename>
        friend class detail::RangedViewDataHolderInterface;

        template<typename>
        friend class detail::ScopedViewDataHolderInterface;

        auto IndexBegin() const -> SizeType { return This()->GetArray().IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->GetArray().IndexEnd(); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetArray().GetObj(n);}
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetArray().GetObj(n);}
    };

    template<bool ORDERED>
    struct ProxyRangedViewDataHolderTrait {
        template<typename ARRAY, typename SUB_TYPE>
        using Type = ProxyRangedViewDataHolder<ARRAY, SUB_TYPE, ORDERED>;
    };

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using RefProxyRangedViewDataHolder = detail::RefViewDataHolder<ARRAY, ProxyRangedViewDataHolderTrait<ORDERED>::template Type>;

    template<__cOnCePt(SimpleRangedArrayLike) ARRAY, bool ORDERED = ARRAY::ORDERED>
    using ValueProxyRangedViewDataHolder = detail::ValueViewDataHolder<ARRAY, ProxyRangedViewDataHolderTrait<ORDERED>::template Type>;
}

#endif //OBJECT_ARRAY_PROXYRANGEDVIEWDATAHOLDER_H
