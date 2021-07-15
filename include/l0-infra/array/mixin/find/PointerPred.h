//
// Created by Darwin Yuan on 2021/7/15.
//

#ifndef OBJECT_ARRAY_37E0601687DB47D998D0E5F7011A6731
#define OBJECT_ARRAY_37E0601687DB47D998D0E5F7011A6731

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    class PointerPred : public T {
        using Self = T;

    public:
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto GetPointerPred(PRED &&pred) const -> auto {
            if constexpr(__wItH_iNdEx_pReD(PRED)) {
                return [&pred](auto *p, auto i) -> bool { return pred(*p, i); };
            } else {
                return [&pred](auto *p) -> bool { return pred(*p); };
            }
        }
    };
}

#endif //OBJECT_ARRAY_37E0601687DB47D998D0E5F7011A6731
