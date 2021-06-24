//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_BYINDEXACCESSOR_H
#define OBJECT_ARRAY_BYINDEXACCESSOR_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/mixin/detail/Mixins.h>
#include <cub/base/InvokeConstMethod.h>

namespace mixin {
    template<_concept::SimpleRangedArrayLike T>
    class ByIndexAccessor : public T {
        using Self = T;

    public:
        using SizeType = typename T::SizeType;
        using ObjectType = typename T::ObjectType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

        auto At(SizeType n) const -> ObjectType const* {
            return n >= IndexEnd() ? nullptr : &GetObj(n + IndexBegin());
        }

        auto At(SizeType n) -> ObjectType * {
            return __INVOKE_CONST_METHOD(At(n));
        }
    };
}

#endif //OBJECT_ARRAY_BYINDEXACCESSOR_H
