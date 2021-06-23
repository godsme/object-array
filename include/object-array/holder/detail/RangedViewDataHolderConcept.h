//
// Created by Darwin Yuan on 2021/6/23.
//

#ifndef OBJECT_ARRAY_RANGEDVIEWDATAHOLDERCONCEPT_H
#define OBJECT_ARRAY_RANGEDVIEWDATAHOLDERCONCEPT_H

#include <object-array/detail/CrtpHelper.h>

namespace holder::detail {
    template<typename T>
    class RangedViewDataHolderConcept {
        dEcL_tHiS(T);
    public:
        using ObjectType = typename T::ObjectType;
        using SizeType = typename T::SizeType;

        auto GetObj(SizeType n) const -> ObjectType const& { return This()->GetObj(n); }
        auto GetObj(SizeType n) -> ObjectType& { return This()->GetObj(n); }
        auto IndexBegin() const -> SizeType { return This()->IndexBegin(); }
        auto IndexEnd() const -> SizeType { return This()->IndexEnd(); }
    };
}

#endif //OBJECT_ARRAY_RANGEDVIEWDATAHOLDERCONCEPT_H
