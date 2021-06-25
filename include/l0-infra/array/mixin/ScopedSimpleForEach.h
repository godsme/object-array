//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SCOPEDSIMPLEFOREACH_H
#define OBJECT_ARRAY_SCOPEDSIMPLEFOREACH_H

#include <l0-infra/array/mixin/ScopedForEach.h>

namespace mixin {
    template<__cOnCePt(ScopedOpVisitable) T>
    struct ScopedSimpleForEach : ScopedForEach<T> {
        using Self = ScopedForEach<T>;
    public:
        using typename Self::SizeType;
        using typename Self::ObjectType;

    public:
        using Self::GetScope;

    public:
        template<bool TO_NON_CONST, __oP_cOnCePt(OP)>
        auto DoForEach(OP &&op) const -> auto {
            return Self::template DoForEach<TO_NON_CONST, false>(GetScope(), std::forward<OP>(op));
        }
    };
}

#endif //OBJECT_ARRAY_SCOPEDSIMPLEFOREACH_H
