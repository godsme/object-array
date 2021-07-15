//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_E62C2AFF9D724B1690F22EC8184983C0
#define OBJECT_ARRAY_2_E62C2AFF9D724B1690F22EC8184983C0

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct IndicesPred : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto GetIndicesPred(PRED&& pred) const -> auto {
            if constexpr(__wItH_iNdEx_pReD(PRED)) {
                return [&pred, &array = T::GetArray()](auto n, auto i) -> bool {
                    return pred(array.GetObject(n), i);
                };
            } else {
                return [&pred, &array = T::GetArray()](auto n) -> bool {
                    return pred(array.GetObject(n));
                };
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_E62C2AFF9D724B1690F22EC8184983C0
