//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_030FE7CEC6134FE08138F6C01CF1D44D
#define OBJECT_ARRAY_2_030FE7CEC6134FE08138F6C01CF1D44D

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ScopeViewMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndex(LESS &&less) const -> Maybe {
            return T::GetArray().Unsafe_ScopeMinElemIndex(T::GetScope(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(LESS &&less) const -> ObjectType const* {
            return T::GetArray().Unsafe_ScopeMinElem(T::GetScope(), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_030FE7CEC6134FE08138F6C01CF1D44D
