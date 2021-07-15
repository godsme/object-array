//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_0B76D4A699C14085BBE8112CADBA24A9
#define OBJECT_ARRAY_2_0B76D4A699C14085BBE8112CADBA24A9

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct UnsafeScopedFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::BitMap;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_ScopeFindIndex(BitMap scope, PRED&& pred) const -> Maybe {
            return T::Unsafe_RangeScopeFindIndex(T::IndexBegin(), T::IndexEnd(), scope, std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Unsafe_ScopeFind(BitMap scope, PRED&& pred) const -> ObjectType const* {
            return T::Unsafe_RangeScopeFind(T::IndexBegin(), T::IndexEnd(), scope, std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_0B76D4A699C14085BBE8112CADBA24A9
