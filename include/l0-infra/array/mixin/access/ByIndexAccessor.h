//
// Created by Darwin Yuan on 2021/7/9.
//

#ifndef OBJECT_ARRAY_2_BYINDEXACCESSOR_3D689E019B6648D287EBD2C319B46811
#define OBJECT_ARRAY_2_BYINDEXACCESSOR_3D689E019B6648D287EBD2C319B46811

#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct ByIndexAccessor : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    private:
        auto Empty() const -> bool {
            return T::IndexBegin() == T::IndexEnd();
        }

    public:
        auto At(SizeType n) const -> ObjectType const* {
            auto index = n + T::IndexBegin();
            return T::IsPresent(index) ? &T::operator[](index) : nullptr;
        }

        auto At(SizeType n) -> ObjectType * {
            return __INVOKE_CONST_METHOD(At(n));
        }

        auto First() const -> auto* {
            return Empty() ? nullptr : &T::operator[](T::IndexBegin());
        }

        auto First() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }

        auto Last() const -> auto* {
            return Empty() ? nullptr : &T::operator[](T::IndexEnd() - 1);
        }

        auto Last() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }
    };
}

#endif //OBJECT_ARRAY_2_BYINDEXACCESSOR_3D689E019B6648D287EBD2C319B46811
