//
// Created by Darwin Yuan on 2021/6/28.
//

#ifndef OBJECT_ARRAY_SCOPEDVIEWDATAHOLDERINTERFACE_H
#define OBJECT_ARRAY_SCOPEDVIEWDATAHOLDERINTERFACE_H

#include <l0-infra/array/detail/CrtpHelper.h>

namespace holder::detail {
    template<typename T>
    class ScopedViewDataHolderInterface {
        dEcL_tHiS(T);
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType   = typename T::SizeType;
        using BitMap     = typename T::BitMap;
        using Owner      = typename T::Owner;

        constexpr static SizeType MAX_SIZE = T::MAX_SIZE;

        using ScopedRangedArrayLike = ScopedViewDataHolderInterface;

        auto GetObj(SizeType n) -> ObjectType& { return This()->GetObj(n); }
        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto IndexBegin() const -> SizeType { return This()->IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->IndexEnd(); }
        auto GetScope() const -> BitMap { return This()->GetScope(); }
    };
}

#endif //OBJECT_ARRAY_SCOPEDVIEWDATAHOLDERINTERFACE_H
