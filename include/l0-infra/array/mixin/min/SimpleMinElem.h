//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_1525C198240A49FF97440844C54BF09C
#define OBJECT_ARRAY_2_1525C198240A49FF97440844C54BF09C

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct SimpleMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndex(LESS &&less) const -> Maybe {
            return T::Unsafe_RangeMinElemIndex(0, T::Num(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(LESS &&less) const -> ObjectType const* {
            return T::Unsafe_RangeMinElem(0, T::Num(), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_1525C198240A49FF97440844C54BF09C
