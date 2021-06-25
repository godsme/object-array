//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SIMPLEMINELEMEXT_H
#define OBJECT_ARRAY_SIMPLEMINELEMEXT_H

#include <object-array/concept/SimpleMinElem.h>
#include <object-array/mixin/SimpleMinElem.h>
#include <object-array/mixin/detail/DefaultLessThan.h>
#include <cub/base/InvokeConstMethod.h>

namespace mixin {
    template<_concept::SimpleMinElem T>
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

        template<_concept::Less<ObjectType> LESS>
        auto MaxElemIndex(LESS &&less) const -> auto {
            return MinElemIndex([&](auto&& l, auto&& r) { return less(r, l); });
        }

        auto MaxElemIndex() const -> auto {
            return MaxElemIndex(detail::DEFAULT_LESS_THAN);
        }

        template<_concept::Less<ObjectType> LESS>
        auto MinElem(LESS &&less) -> auto* {
            return __INVOKE_CONST_METHOD(MinElem(std::forward<LESS>(less)));
        }

        auto MinElem() const -> auto* {
            return MinElem(detail::DEFAULT_LESS_THAN);
        }

        auto MinElem() -> auto* {
            return __INVOKE_CONST_METHOD(MinElem());
        }

        template<_concept::Less<ObjectType> LESS>
        auto MaxElem(LESS &&less) const -> auto* {
            return MinElem([&](auto&& l, auto&& r) { return less(r, l); });
        }

        template<_concept::Less<ObjectType> LESS>
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
