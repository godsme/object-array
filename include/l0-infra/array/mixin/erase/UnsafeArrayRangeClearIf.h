//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_431CFD52E52A4BF9A5E0C6D6D777F60A
#define OBJECT_ARRAY_431CFD52E52A4BF9A5E0C6D6D777F60A

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct UnsafeArrayRangeClearIf : T {
        using typename T::ObjectType;
        using typename T::SizeType;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto Unsafe_RangeClearIf(SizeType from, SizeType until, PRED&& pred) -> void {
            if(from == until) return;
            for(int i = until - 1; i >= from; --i) {
                if(T::IsPresent(i) && pred(T::GetObject(i))) T::Erase(i);
            }
        }
    };
}

#endif //OBJECT_ARRAY_431CFD52E52A4BF9A5E0C6D6D777F60A
