//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_C8F35098915D43E79116A9F79898F425
#define OBJECT_ARRAY_C8F35098915D43E79116A9F79898F425

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct RangeViewCleanUpIf : T {
        using typename T::OffsetType;
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) && -> void {
            T::GetArray().Unsafe_RangeCleanUpIf(T::IndexBegin(), T::IndexEnd(), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) & = delete;
    };
}

#endif //OBJECT_ARRAY_C8F35098915D43E79116A9F79898F425
