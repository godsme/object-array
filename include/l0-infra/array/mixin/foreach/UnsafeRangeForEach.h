//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_C450A36A70E84E989AE06F95BDA94834
#define OBJECT_ARRAY_2_C450A36A70E84E989AE06F95BDA94834

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct UnsafeRangeForEach : T {
        using typename T::SizeType;
        using typename T::ObjectType;

    public:
        template<__oP_cOnCePt(OP)>
        auto Unsafe_RangeForEach(SizeType from, SizeType until, OP &&op) const -> auto {
            return T::template RangeForEach<false>(from, until, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto Unsafe_RangeForEach(SizeType from, SizeType until, OP &&op) -> auto {
            return T::template RangeForEach<true>(from, until, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_C450A36A70E84E989AE06F95BDA94834
