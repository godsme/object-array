//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_6279E8D874DD42B6A155B20161300CD4
#define OBJECT_ARRAY_2_6279E8D874DD42B6A155B20161300CD4

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct SliceMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto MinElemIndex(LESS &&less) const -> Maybe {
            return T::GetArray().Unsafe_RangeMinElemIndex(T::IndexBegin(), T::IndexEnd(), std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto MinElem(LESS &&less) const -> ObjectType const* {
            return T::GetArray().Unsafe_RangeMinElem(T::IndexBegin(), T::IndexEnd(), std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_6279E8D874DD42B6A155B20161300CD4
