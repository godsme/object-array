//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDERINTERFACE_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDERINTERFACE_H

#include <l0-infra/array/detail/CrtpHelper.h>

namespace holder::detail {
    template<typename T>
    class RangedViewDataHolderInterface {
        dEcL_tHiS(T);
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType   = typename T::SizeType;
        using ArrayType  = typename T::ArrayType;

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetObj(n); }
        auto IndexBegin() const -> SizeType { return This()->IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->IndexEnd(); }
        auto GetArray() const -> decltype(auto) { return This()->This()->GetArray(); }
        auto GetArray() -> decltype(auto) { return This()->This()->GetArray(); }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDERINTERFACE_H
