//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_ADC72DD7B766475A966022DDDF68D1D7
#define OBJECT_ARRAY_ADC72DD7B766475A966022DDDF68D1D7

#include <l0-infra/array/concept/Op.h>
#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct ArrayPredForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        template<typename PRED, __oP_cOnCePt(OP), __wItH_pReD(PRED)>
        auto PredForEach(PRED&& pred, OP &&op) const -> auto {
            return T::Unsafe_RangePredForEach(T::IndexBegin(), T::IndexEnd(), std::forward<PRED>(pred), std::forward<OP>(op));
        }

        template<typename PRED, __oP_cOnCePt(OP), __wItH_pReD(PRED)>
        auto PredForEach(SizeType from, SizeType until, PRED&& pred, OP &&op) -> auto {
            return T::Unsafe_RangePredForEach(T::IndexBegin(), T::IndexEnd(), std::forward<PRED>(pred), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_ADC72DD7B766475A966022DDDF68D1D7
