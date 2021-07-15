//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_5BA8CA7C24264037BDAD3843C92FAB29
#define OBJECT_ARRAY_2_5BA8CA7C24264037BDAD3843C92FAB29

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct IndicesOp : T {
        using T::GetArray;
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto GetIndicesOp(OP &&op) const -> auto {
            auto&& array = T::template GetArray<TO_NON_CONST>();
            if constexpr(__wItH_iNdEx_Op(OP)) {
                return [&op, &array](auto n, auto i) -> auto {
                    return op(array.GetObject(n), i);
                };
            } else {
                return [&op, &array](auto n) -> auto {
                    return op(array.GetObject(n));
                };
            }
        }
    };
}

#endif //OBJECT_ARRAY_2_5BA8CA7C24264037BDAD3843C92FAB29
