//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_CONTINUOUSARRAYDATAHOLDERINTERFACE_H
#define OBJECT_ARRAY_CONTINUOUSARRAYDATAHOLDERINTERFACE_H

#include <object-array/holder/detail/ArrayDataHolderInterface.h>

namespace holder::detail {
    template<typename DATA_HOLDER>
    class ContinuousArrayDataHolderInterface : public ArrayDataHolderInterface<DATA_HOLDER> {
        dEcL_tHiS(DATA_HOLDER);
    public:
        using SizeType = typename DATA_HOLDER::SizeType;
        using Trait = typename DATA_HOLDER::Trait;

        auto Num() const -> SizeType { return This()->num; }
        auto Num() -> decltype(auto) { return (This()->num); }
    };
}

#endif //OBJECT_ARRAY_CONTINUOUSARRAYDATAHOLDERINTERFACE_H
