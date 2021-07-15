//
// Created by Darwin Yuan on 2021/7/13.
//

#ifndef OBJECT_ARRAY_2_5D9EC23ADC8941A78C0572601F31FCEF
#define OBJECT_ARRAY_2_5D9EC23ADC8941A78C0572601F31FCEF

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct RangeFactory {
        template<__pRed_CoNcEpT(PRED)>
        auto Range(PRED&& pred) & -> auto {
            auto begin = T::FindIndex(pred);
            if(!begin) {
                return T::
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_5D9EC23ADC8941A78C0572601F31FCEF
