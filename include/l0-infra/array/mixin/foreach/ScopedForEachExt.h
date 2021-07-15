//
// Created by Darwin Yuan on 2021/7/10.
//

#ifndef OBJECT_ARRAY_2_33EC25B00D4D4CC0B5164954AE8DE98C
#define OBJECT_ARRAY_2_33EC25B00D4D4CC0B5164954AE8DE98C

#include <l0-infra/array/concept/Op.h>

namespace mixin {
    template<typename T>
    struct ScopedForEachExt : T {
        using typename T::BitMap;
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        using T::ForEach;

        template<__oP_cOnCePt(OP)>
        auto ForEach(BitMap scope, OP &&op) const -> auto {
            return T::template ScopeForEach<false>(scope, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto ForEach(BitMap scope, OP &&op) -> auto {
            return T::template ScopeForEach<true>(scope, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto ForEachEx(BitMap excluded, OP &&op) const -> auto {
            return ForEach(~excluded, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto ForEachEx(BitMap excluded, OP &&op) -> auto {
            return ForEach(~excluded, std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_2_33EC25B00D4D4CC0B5164954AE8DE98C
