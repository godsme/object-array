//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYDATAHOLDERINTERFACE_H
#define OBJECT_ARRAY_CONTINUOUSARRAYDATAHOLDERINTERFACE_H

#include <l0-infra/array/holder/detail/ArrayDataHolderInterface.h>

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ContinuousArrayDataHolderInterface : public ArrayDataHolderInterface<DATA_HOLDER> {
        dEcL_tHiS(DATA_HOLDER);
    public:
        using SizeType = typename DATA_HOLDER::SizeType;
        using Trait    = typename DATA_HOLDER::Trait;
        using Owner    = typename DATA_HOLDER::Owner;

        auto Num() const -> SizeType { return This()->num; }
        auto Num() -> decltype(auto) { return (This()->num); }
    };

    template<typename DATA_HOLDER>
    class ContinuousArrayDataHolderInterface1 : public ArrayDataHolderInterface1<DATA_HOLDER> {
        using Holder = typename DATA_HOLDER::Inner;
        dEcL_tHiS(Holder);
    public:
        using SizeType = typename DATA_HOLDER::SizeType;
        using Trait    = typename DATA_HOLDER::Trait;
        using Owner    = typename DATA_HOLDER::Owner;

        auto Num() const -> SizeType { return This()->num; }
        auto Num() -> decltype(auto) { return (This()->num); }
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYDATAHOLDERINTERFACE_H
