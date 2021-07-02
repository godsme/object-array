//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SIMPLEMINELEMEXT_H
#define OBJECT_ARRAY_SIMPLEMINELEMEXT_H

#include <l0-infra/array/concept/SimpleMinElem.h>
#include <l0-infra/array/mixin/simple/SimpleMinElem.h>
#include <l0-infra/array/mixin/detail/DefaultLessThan.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<__cOnCePt(SimpleMinElem) T>
    class SimpleMinElemExt : public T {
        using Self = T;

    public:
        using typename Self::ObjectType;

    public:
        using Self::MinElemIndex;
        using Self::MinElem;

        auto MinElemIndex() const -> auto {
            return MinElemIndex(detail::DEFAULT_LESS_THAN);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElemIndex(LESS &&less) const -> auto {
            return MinElemIndex([&](auto&& l, auto&& r) { return less(r, l); });
        }

        auto MaxElemIndex() const -> auto {
            return MaxElemIndex(detail::DEFAULT_LESS_THAN);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(LESS &&less) -> auto* {
            return __INVOKE_CONST_METHOD(MinElem(std::forward<LESS>(less)));
        }

        auto MinElem() const -> auto* {
            return MinElem(detail::DEFAULT_LESS_THAN);
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
            return MaxElem(detail::DEFAULT_LESS_THAN);
        }

        auto MaxElem() -> ObjectType * {
            return __INVOKE_CONST_METHOD(MaxElem());
        }
    };
}

#endif //OBJECT_ARRAY_SIMPLEMINELEMEXT_H
