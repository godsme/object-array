//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_0E561D3712074CB4A70F2ADC09102DDF
#define OBJECT_ARRAY_0E561D3712074CB4A70F2ADC09102DDF

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct ArrayRangeCleanUpIf_R : T {
        using typename T::OffsetType;
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        using T::CleanUpIf;
        using T::RangeCleanUpIf;
        using T::CleanUpFromIf;
        using T::CleanUpUntilIf;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpIf(PRED&& pred) && -> ThisType {
            return T::CleanUpIf(std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto RangeCleanUpIf(OffsetType from, OffsetType until, PRED&& pred) && -> ThisType {
            return T::RangeCleanUpIf(from, until, std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpFromIf(OffsetType from, PRED&& pred) && -> ThisType {
            return T::CleanUpFromIf(from, std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto CleanUpUntilIf(OffsetType until, PRED&& pred) && -> ThisType {
            return T::CleanUpUntilIf(until, std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_0E561D3712074CB4A70F2ADC09102DDF
