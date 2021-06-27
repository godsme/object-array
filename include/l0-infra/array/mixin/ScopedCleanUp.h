//
// Created by Darwin Yuan on 2021/6/25.
//

#ifndef OBJECT_ARRAY_SCOPEDCLEANUP_H
#define OBJECT_ARRAY_SCOPEDCLEANUP_H

#include <l0-infra/array/concept/SimpleFind.h>
#include <l0-infra/array/concept/SimpleMutable.h>

namespace mixin {
    template<__cOnCePt(SimpleRangedMutable) T>
    class ScopedCleanUp : public T {
        using Self = T;
    public:
        using typename Self::BitMap;

        using Self::IndexBegin;
        using Self::IndexEnd;

        using Self::Erase;

    public:
        auto CleanUp(BitMap scope) -> void {
            if(IndexEnd() == IndexBegin()) return;
            for(auto i=IndexEnd()-1; i>=IndexBegin(); --i) {
                if(scope[i]) Erase(i);
            }
        }

        auto CleanUpEx(BitMap excluded) -> void {
            CleanUp(~excluded);
        }

    };
}

#endif //OBJECT_ARRAY_SCOPEDCLEANUP_H