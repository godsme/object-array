//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_AC02627AAB7D42D3BAB7ECFEA406A049
#define OBJECT_ARRAY_2_AC02627AAB7D42D3BAB7ECFEA406A049

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class ScopedSimpleFind : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto FindIndex(PRED&& pred) const -> Maybe {
            return T::GetArray().Unsafe_ScopeFindIndex(T::GetScope(), std::forward<PRED>(pred));
        }

        template<__pRed_CoNcEpT(PRED)>
        auto Find(PRED&& pred) const -> ObjectType const* {
            return T::GetArray().Unsafe_ScopeFind(T::GetScope(), std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_2_AC02627AAB7D42D3BAB7ECFEA406A049
