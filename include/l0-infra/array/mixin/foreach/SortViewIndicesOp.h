//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_F0E12B1ECBCD4C8D9538037BA3A830EB
#define OBJECT_ARRAY_2_F0E12B1ECBCD4C8D9538037BA3A830EB

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct SortViewIndicesOp : T {
        using T::GetArray;
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto GetIndicesOp(OP &&op) const -> auto {
            auto&& array = T::template GetArray<TO_NON_CONST>();
            return [&op, &array = T::template GetArray<TO_NON_CONST>()](auto n) -> auto {
                if constexpr(__wItH_iNdEx_Op(OP)) {
                    return op(array.GetObject(n), n);
                } else {
                    return op(array.GetObject(n));
                }
            };
        }
    };
}

#endif //OBJECT_ARRAY_2_F0E12B1ECBCD4C8D9538037BA3A830EB
