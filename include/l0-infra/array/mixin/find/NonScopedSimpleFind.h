//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_7BF07355492E4ADBA28E66112EF24D29
#define OBJECT_ARRAY_2_7BF07355492E4ADBA28E66112EF24D29

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct NonScopedSimpleFind : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED&& pred) const -> Maybe {
            return T::Unsafe_RangeFindIndex(0, T::Num(), std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED&& pred) const -> ObjectType const* {
            return T::Unsafe_RangeFind(0, T::Num(), std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto FindRange(PRED&& pred) const -> std::pair<SizeType, SizeType> {
            return T::Unsafe_RangeFindRange(0, T::Num(), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_7BF07355492E4ADBA28E66112EF24D29
