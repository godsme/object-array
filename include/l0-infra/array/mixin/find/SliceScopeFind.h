//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_271387CE84CA4AF9937200FC558A166A
#define OBJECT_ARRAY_2_271387CE84CA4AF9937200FC558A166A

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct SliceScopeFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;
        using typename T::BitMap;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto ScopeFindIndex(BitMap scope, PRED&& pred) const -> Maybe {
            return T::template GetArray().Unsafe_RangeScopeFindIndex(T::IndexBegin(), T::IndexEnd(), scope, std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto ScopeFind(BitMap scope, PRED&& pred) const -> ObjectType const* {
            return T::GetArray().Unsafe_RangeScopeFind(T::IndexBegin(), T::IndexEnd(), scope, std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_271387CE84CA4AF9937200FC558A166A
