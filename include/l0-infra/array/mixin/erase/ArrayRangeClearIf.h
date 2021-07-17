//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_6B9476C9FA4F44E585C4B438236DF371
#define OBJECT_ARRAY_6B9476C9FA4F44E585C4B438236DF371

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct ArrayRangeClearIf : T {
        using typename T::OffsetType;
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearIf(PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeClearIf(0, T::IndexEnd(), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearIf(PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeClearIf(OffsetType from, OffsetType until, PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeClearIf(from.ToIndex(T::IndexEnd()), until.ToIndex(T::IndexEnd()), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeClearIf(OffsetType from, OffsetType until, PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearFromIf(OffsetType from, PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeClearIf(from.ToIndex(T::IndexEnd()), T::IndexEnd(), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearFromIf(OffsetType from, PRED&& pred) && = delete;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearUntilIf(OffsetType until, PRED&& pred) & -> ThisType& {
            T::Unsafe_RangeClearIf(0, until.ToIndex(T::IndexEnd()), std::forward<PRED>(pred));
            return T::ToThisType();
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearUntilIf(OffsetType until, PRED&& pred) && = delete;
    };
}

#endif //OBJECT_ARRAY_6B9476C9FA4F44E585C4B438236DF371
