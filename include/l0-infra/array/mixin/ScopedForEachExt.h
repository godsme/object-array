//
// Created by Darwin Yuan on 2021/6/24.
//

#ifndef OBJECT_ARRAY_SCOPEDFOREACHEXT_H
#define OBJECT_ARRAY_SCOPEDFOREACHEXT_H

#include <l0-infra/array/mixin/ScopedForEach.h>
#include <utility>

namespace mixin {
    template<typename T>
    class ScopedForEachExt : public T {
        using Self = T;

    public:
        using typename Self::BitMap;
        using typename Self::ObjectType;
        using typename Self::SizeType;

    public:
        using Self::ForEach;

        template<__oP_cOnCePt(OP)>
        auto ForEach(BitMap scope, OP &&op) const -> auto {
            return Self::template DoScopeForEach<false, true>(scope, std::forward<OP>(op));
        }

        template<__oP_cOnCePt(OP)>
        auto ForEach(BitMap scope, OP &&op) -> auto {
            return Self::template DoScopeForEach<true, true>(scope, std::forward<OP>(op));
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

#endif //OBJECT_ARRAY_SCOPEDFOREACHEXT_H
