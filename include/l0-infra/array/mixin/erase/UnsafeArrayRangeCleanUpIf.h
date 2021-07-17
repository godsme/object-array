//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_A1FD98F195804A578534A842D4FCF698
#define OBJECT_ARRAY_A1FD98F195804A578534A842D4FCF698

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct UnsafeArrayRangeCleanUpIf : T {
        using typename T::ObjectType;
        using typename T::SizeType;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto Unsafe_RangeCleanUpIf(SizeType from, SizeType until, PRED&& pred) -> void {
            if(from == until) return;
            for(int i = until - 1; i >= from; --i) {
                if(T::IsPresent(i) && pred(T::GetObject(i))) T::Erase(i);
            }
        }
    };
}

#endif //OBJECT_ARRAY_A1FD98F195804A578534A842D4FCF698
