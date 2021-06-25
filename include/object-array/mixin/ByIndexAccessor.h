//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_BYINDEXACCESSOR_H
#define OBJECT_ARRAY_BYINDEXACCESSOR_H

#include <object-array/concept/RangedArrayLike.h>
#include <object-array/mixin/detail/Mixins.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedArrayLike) T>
    class ByIndexAccessor : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;

        using Self::IndexBegin;
        using Self::IndexEnd;
        using Self::GetObj;

        auto At(SizeType n) const -> ObjectType const* {
            auto index = n + IndexBegin();
            return index >= IndexEnd() ? nullptr : &GetObj(index);
        }

        auto At(SizeType n) -> ObjectType * {
            return __INVOKE_CONST_METHOD(At(n));
        }

        auto First() const -> auto* {
            return IndexBegin() == IndexEnd() ? nullptr : &GetObj(IndexBegin());
        }

        auto First() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }

        auto Last() const -> auto* {
            return IndexBegin() == IndexEnd() ? nullptr : &GetObj(IndexEnd() - 1);
        }

        auto Last() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }
    };
}

#endif //OBJECT_ARRAY_BYINDEXACCESSOR_H
