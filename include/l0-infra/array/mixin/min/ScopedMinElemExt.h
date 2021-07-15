//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_09951C992E294815A7D84507D77E189F
#define OBJECT_ARRAY_2_09951C992E294815A7D84507D77E189F

#include <l0-infra/array/concept/Less.h>
#include <l0-infra/base/InvokeConstMethod.h>

namespace mixin {
    template<typename T>
    struct ScopedMinElemExt : T {
        using typename T::Maybe;
        using typename T::BitMap;
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        using T::MinElem;
        using T::MaxElem;
        using T::MinElemIndex;
        using T::MaxElemIndex;

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndex(BitMap scope, LESS &&less) const -> Maybe {
            return T::Unsafe_ScopeMinElemIndex(scope.Mask(T::IndexBegin(), T::IndexEnd()), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndexEx(BitMap excluded, LESS &&less) const -> Maybe {
            return MinElemIndex(~excluded, std::forward<LESS>(less));
        }

        auto MinElemIndex(BitMap scope) const -> Maybe {
            return MinElemIndex(scope, T::GetLess());
        }

        auto MinElemIndexEx(BitMap excluded) const -> Maybe {
            return MinElemIndexEx(excluded, T::GetLess());
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(BitMap scope, LESS &&less) const -> ObjectType const * {
            return T::Unsafe_ScopeMinElem(scope.Mask(T::IndexBegin(), T::IndexEnd()), std::forward<LESS>(less));
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
            return MinElem(scope, T::GetLess());
        }

        auto MinElem(BitMap scope) -> ObjectType * {
            return __INVOKE_CONST_METHOD(MinElem(scope));
        }

        auto MinElemEx(BitMap excluded) const -> ObjectType const * {
            return MinElemEx(excluded, T::GetLess());
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
            return MinElemIndex(scope, T::GetGreater());
        }

        auto MaxElemIndexEx(BitMap excluded) const -> Maybe {
            return MinElemIndexEx(excluded, T::GetGreater());
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
            return MaxElem(scope, T::GetLess());
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
            return MaxElemEx(scope, T::GetLess());
        }

        auto MaxElemEx(BitMap scope) -> auto* {
            return __INVOKE_CONST_METHOD(MaxElemEx(scope));
        }
    };
}

#endif //OBJECT_ARRAY_2_09951C992E294815A7D84507D77E189F
