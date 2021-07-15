//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_7CD6F49BA048467C9CBC0C5C50698D43
#define OBJECT_ARRAY_2_7CD6F49BA048467C9CBC0C5C50698D43

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct SimpleForEachExt : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<__oP_cOnCePt(OP)>
        auto ForEach(OP &&op) const -> auto {
            return T::template DoForEach<false>(std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto ForEach(OP &&op) -> auto {
            return T::template DoForEach<true>(std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_7CD6F49BA048467C9CBC0C5C50698D43
