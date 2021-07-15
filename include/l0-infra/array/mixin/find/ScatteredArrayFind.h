//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_DA5779A4DCCA414EB355E02F4A32E626
#define OBJECT_ARRAY_2_DA5779A4DCCA414EB355E02F4A32E626

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct ScatteredArrayFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED&& pred) const -> Maybe {
            return T::Unsafe_RangeScopeFindIndex(0, T::MAX_SIZE, T::GetScope(), std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED&& pred) const -> ObjectType const* {
            return T::Unsafe_RangeScopeFind(0, T::MAX_SIZE, T::GetScope(), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_DA5779A4DCCA414EB355E02F4A32E626
