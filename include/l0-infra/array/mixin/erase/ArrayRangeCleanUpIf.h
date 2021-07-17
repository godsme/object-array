//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_BA88005C50414327A809C9FAFAAC5537
#define OBJECT_ARRAY_BA88005C50414327A809C9FAFAAC5537

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct ArrayRangeCleanUpIf : T {
        using typename T::OffsetType;
        using typename T::ObjectType;
        using typename T::SizeType;

    public:
        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) & -> void {
            T::Unsafe_CleanUpIf(0, T::Num(), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeCleanUpIf(OffsetType from, OffsetType until, PRED&& pred) & -> void {
            T::Unsafe_CleanUpIf(from.ToIndex(T::Num()), until.ToIndex(T::Num()), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeCleanUpIf(OffsetType from, OffsetType until, PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpFromIf(OffsetType from, PRED&& pred) & -> void {
            T::Unsafe_CleanUpIf(from.ToIndex(T::Num()), T::Num(), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpFromIf(OffsetType from, PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpUntilIf(OffsetType until, PRED&& pred) & -> void {
            T::Unsafe_CleanUpIf(0, until.ToIndex(T::Num()), std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpUntilIf(OffsetType until, PRED&& pred) && = delete;
    };
}

#endif //OBJECT_ARRAY_BA88005C50414327A809C9FAFAAC5537
