//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_808AB21DC5114AE4BE0C0A8ABE978D0B
#define OBJECT_ARRAY_2_808AB21DC5114AE4BE0C0A8ABE978D0B

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct SortViewIndicesPred : T {
        using typename T::SizeType;
        using typename T::ObjectType;
        using typename T::Maybe;

    public:
        template<__pRed_CoNcEpT(PRED)>
        auto GetIndicesPred(PRED&& pred) const -> auto {
            return [&pred, &array = T::GetArray()](auto n) -> bool {
                if constexpr(__wItH_iNdEx_pReD(PRED)) {
                    return pred(array.GetObject(n), n);
                } else {
                    return pred(array.GetObject(n));
                }
            };
        }
    };
}

#endif //OBJECT_ARRAY_2_808AB21DC5114AE4BE0C0A8ABE978D0B
