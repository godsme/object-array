//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_B31AC837C6EE4F09BD01B385CAF91027
#define OBJECT_ARRAY_2_B31AC837C6EE4F09BD01B385CAF91027

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct SimpleMinElemExt : T {
        using typename T::ObjectType;

    public:
        using T::MinElemIndex;
        using T::MinElem;

        auto MinElemIndex() const -> auto {
            return MinElemIndex(T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElemIndex(LESS &&less) const -> auto {
            return MinElemIndex([&](auto&& l, auto&& r) { return less(r, l); });
        }

        auto MaxElemIndex() const -> auto {
            return MaxElemIndex(T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(LESS &&less) -> auto* {
            return __INVOKE_CONST_METHOD(MinElem(std::forward<LESS>(less)));
        }

        auto MinElem() const -> auto* {
            return MinElem(T::GetLess());
        }

        auto MinElem() -> auto* {
            return __INVOKE_CONST_METHOD(MinElem());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElem(LESS &&less) const -> auto* {
            return MinElem([&](auto&& l, auto&& r) { return less(r, l); });
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElem(LESS &&less) -> auto* {
            return __INVOKE_CONST_METHOD(MaxElem(std::forward<LESS>(less)));
        }

        auto MaxElem() const -> auto* {
            return MaxElem(T::GetLess());
        }

        auto MaxElem() -> ObjectType * {
            return __INVOKE_CONST_METHOD(MaxElem());
        }
    };
}

#endif //OBJECT_ARRAY_2_B31AC837C6EE4F09BD01B385CAF91027
