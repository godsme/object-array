//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_FBB30DAC54DC449FA537204BE194FD02
#define OBJECT_ARRAY_2_FBB30DAC54DC449FA537204BE194FD02

#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct ArrayByIndexAccessor : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        auto At(SizeType n) const -> ObjectType const* {
            return n >= T::Num() ? nullptr : &T::operator[](n);
        }

        auto At(SizeType n) -> ObjectType * {
            return __INVOKE_CONST_METHOD(At(n));
        }

        auto First() const -> auto* {
            return (T::Num() == 0) ? nullptr : &T::operator[](0);
        }

        auto First() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }

        auto Last() const -> auto* {
            return (T::Num() == 0) ? nullptr : &T::operator[](T::Num() - 1);
        }

        auto Last() -> auto* {
            return __INVOKE_CONST_METHOD(Last());
        }
    };
}

#endif //OBJECT_ARRAY_2_FBB30DAC54DC449FA537204BE194FD02
