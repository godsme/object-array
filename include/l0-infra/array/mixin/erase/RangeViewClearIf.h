//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_DFCC0EA3634C40568A617EF291B1CCEF
#define OBJECT_ARRAY_DFCC0EA3634C40568A617EF291B1CCEF

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct RangeViewClearIf : T {
        using typename T::OffsetType;
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        // r-value slice could do ClearIf, because we don't have to maintain
        // the integrity of Slice.

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearIf(PRED&& pred) && -> void {
            T::GetArray().Unsafe_RangeClearIf(T::IndexBegin(), T::IndexEnd(), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearIf(PRED&& pred) & = delete;
    };
}

#endif //OBJECT_ARRAY_DFCC0EA3634C40568A617EF291B1CCEF
