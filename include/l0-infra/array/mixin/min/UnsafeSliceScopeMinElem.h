//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_E52AE8D0F9D0420A9F92CE97421A016C
#define OBJECT_ARRAY_2_E52AE8D0F9D0420A9F92CE97421A016C

#include <l0-infra/array/concept/Less.h>

namespace mixin {
    template<typename T>
    struct UnsafeSliceScopeMinElem : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;
        using typename T::Maybe;

    public:
        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeMinElemIndex(BitMap scope, LESS &&less) const -> Maybe {
            return T::GetArray().Unsafe_RangeScopeMinElemIndex(T::IndexBegin(), T::IndexEnd(), scope, std::forward<LESS>(less));
        }

        template<__lEsS_cOnCePt(LESS)>
        auto Unsafe_ScopeMinElem(BitMap scope, LESS &&less) const -> ObjectType const* {
            return T::GetArray().Unsafe_RangeScopeMinElem(T::IndexBegin(), T::IndexEnd(), scope, std::forward<LESS>(less));
        }
    };
}

#endif //OBJECT_ARRAY_2_E52AE8D0F9D0420A9F92CE97421A016C
