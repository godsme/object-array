//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SCOPEDMINELEMEXT_H
#define OBJECT_ARRAY_SCOPEDMINELEMEXT_H

#include <l0-infra/array/mixin/scoped/ScopedMinElem.h>
#include <l0-infra/array/mixin/detail/DefaultLessThan.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<__cOnCePt(ConstRangedArrayLike) T>
    class ScopedMinElemExt : public T {
        using Self = T;
    public:
        using typename Self::Maybe;
        using typename Self::BitMap;
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        using Self::MinElem;
        using Self::MaxElem;
        using Self::MinElemIndex;
        using Self::MaxElemIndex;

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndex(BitMap scope, LESS &&less) const -> Maybe {
            return Self::template DoMinElemIndex<true>(scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexEx(BitMap excluded, LESS &&less) const -> Maybe {
            return MinElemIndex(~excluded, std::forward<LESS>(less));
        }

        auto MinElemIndex(BitMap scope) const -> Maybe {
            return MinElemIndex(scope, detail::DEFAULT_LESS_THAN);
        }

        auto MinElemIndexEx(BitMap excluded) const -> Maybe {
            return MinElemIndexEx(excluded, detail::DEFAULT_LESS_THAN);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(BitMap scope, LESS &&less) const -> ObjectType const * {
            return Self::template MinElem(scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(BitMap scope, LESS &&less) -> auto* {
            return __INVOKE_CONST_METHOD(MinElem(scope, std::forward<LESS>(less)));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemEx(BitMap excluded, LESS &&less) const -> ObjectType const * {
            return MinElem(~excluded, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemEx(BitMap excluded, LESS &&less) -> ObjectType * {
            return __INVOKE_CONST_METHOD(MinElemEx(excluded, std::forward<LESS>(less)));
        }

        auto MinElem(BitMap scope) const -> ObjectType const * {
            return MinElem(scope, detail::DEFAULT_LESS_THAN);
        }

        auto MinElem(BitMap scope) -> ObjectType * {
            return __INVOKE_CONST_METHOD(MinElem(scope));
        }

        auto MinElemEx(BitMap excluded) const -> ObjectType const * {
            return MinElemEx(excluded, detail::DEFAULT_LESS_THAN);
        }

        auto MinElemEx(BitMap excluded) -> ObjectType * {
            return __INVOKE_CONST_METHOD(MinElemEx(excluded));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElemIndex(BitMap excluded, LESS &&less) const -> Maybe {
            return MinElemIndex(excluded, [&](auto &&l, auto r) { return less(r, l); });
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElemIndexEx(BitMap excluded, LESS &&less) const -> Maybe {
            return MinElemIndexEx(excluded, [&](auto &&l, auto r) { return less(r, l); });
        }

        auto MaxElemIndex(BitMap scope) const -> std::optional<SizeType> {
            return MinElemIndex(scope, detail::DEFAULT_GREATER_THAN);
        }

        auto MaxElemIndexEx(BitMap excluded) const -> Maybe {
            return MinElemIndexEx(excluded, detail::DEFAULT_GREATER_THAN);
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElem(BitMap scope, LESS &&less) const -> auto {
            return MinElem(scope, [&](auto &&l, auto r) { return less(r, l); });
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElem(BitMap scope, LESS &&less) -> auto* {
            return __INVOKE_CONST_METHOD(MaxElem(scope, std::forward<LESS>(less)));
        }

        auto MaxElem(BitMap scope) const -> auto {
            return MaxElem(scope, detail::DEFAULT_LESS_THAN);
        }

        auto MaxElem(BitMap scope) -> auto {
            return __INVOKE_CONST_METHOD(MaxElem(scope));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElemEx(BitMap excluded, LESS &&less) const -> auto {
            return MaxElem(~excluded, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MaxElemEx(BitMap excluded, LESS &&less) -> auto* {
            return __INVOKE_CONST_METHOD(MaxElemEx(excluded, std::forward<LESS>(less)));
        }

        auto MaxElemEx(BitMap scope) const -> auto* {
            return MaxElemEx(scope, detail::DEFAULT_LESS_THAN);
        }

        auto MaxElemEx(BitMap scope) -> auto* {
            return __INVOKE_CONST_METHOD(MaxElemEx(scope));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDMINELEMEXT_H
