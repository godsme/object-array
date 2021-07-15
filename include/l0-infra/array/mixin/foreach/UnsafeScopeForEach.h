//
// Created by Darwin Yuan on 2021/7/11.
//

#ifndef OBJECT_ARRAY_2_0E96294CEE6442E8B239FEDFE8290090
#define OBJECT_ARRAY_2_0E96294CEE6442E8B239FEDFE8290090

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct UnsafeScopedForEach : T {
        using typename T::ObjectType;
        using typename T::SizeType;
        using typename T::BitMap;

    public:
        template<__oP_cOnCePt(OP)>
        auto Unsafe_ScopeForEach(BitMap scope, OP &&op) const -> auto {
            return T::template Unsafe_ScopeForEach<false>(scope, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto Unsafe_ScopeForEach(BitMap scope, OP &&op) -> auto {
            return T::template Unsafe_ScopeForEach<true>(scope, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_0E96294CEE6442E8B239FEDFE8290090
