//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_A7513A8874C7477684F692C04A28E6B5
#define OBJECT_ARRAY_2_A7513A8874C7477684F692C04A28E6B5

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct ScatteredArrayMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndex(LESS &&less) const -> Maybe {
            return T::Unsafe_RangeScopeMinElemIndex(0, T::MAX_SIZE, T::GetScope(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(LESS &&less) const -> ObjectType const* {
            return T::Unsafe_RangeScopeMinElem(0, T::MAX_SIZE, T::GetScope(), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_A7513A8874C7477684F692C04A28E6B5
