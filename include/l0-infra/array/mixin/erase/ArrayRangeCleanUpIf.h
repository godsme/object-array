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

    protected:
        using typename T::ThisType;

    public:
        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeCleanUpIf(0, T::IndexEnd(), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeCleanUpIf(OffsetType from, OffsetType until, PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeCleanUpIf(from.ToIndex(T::IndexEnd()), until.ToIndex(T::IndexEnd()), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeCleanUpIf(OffsetType from, OffsetType until, PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpFromIf(OffsetType from, PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeCleanUpIf(from.ToIndex(T::IndexEnd()), T::IndexEnd(), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpFromIf(OffsetType from, PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpUntilIf(OffsetType until, PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeCleanUpIf(0, until.ToIndex(T::IndexEnd()), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpUntilIf(OffsetType until, PRED&& pred) && = delete;
    };
}

#endif //OBJECT_ARRAY_BA88005C50414327A809C9FAFAAC5537
