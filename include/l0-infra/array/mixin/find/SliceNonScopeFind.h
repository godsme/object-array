//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_DB04C63E7C454E87827CB6D13D943A29
#define OBJECT_ARRAY_2_DB04C63E7C454E87827CB6D13D943A29

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct SliceNonScopeFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED&& pred) const -> Maybe {
            return T::GetArray().Unsafe_RangeFindIndex(T::IndexBegin(), T::IndexEnd(), std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED&& pred) const -> ObjectType const* {
            return T::GetArray().Unsafe_RangeFind(T::IndexBegin(), T::IndexEnd(), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_DB04C63E7C454E87827CB6D13D943A29
