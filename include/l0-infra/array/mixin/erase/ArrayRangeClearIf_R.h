//
// Created by Darwin Yuan on 2021/7/17.
//

#ifndef OBJECT_ARRAY_EA0E1E7F001A4C02ABA7367B15C9F753
#define OBJECT_ARRAY_EA0E1E7F001A4C02ABA7367B15C9F753

#include <l0-infra/array/concept/Pred.h>

namespace mixin {
    template<typename T>
    struct ArrayRangeClearIf_R : T {
        using typename T::OffsetType;
        using typename T::ObjectType;
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        using T::ClearIf;
        using T::ClearFromIf;
        using T::ClearUntilIf;

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearIf(PRED&& pred) && -> ThisType {
            return T::ClearIf(std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearIf(OffsetType from, OffsetType until, PRED&& pred) && -> ThisType {
            return T::ClearIf(from, until, std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearFromIf(OffsetType from, PRED&& pred) && -> ThisType {
            return T::ClearFromIf(from, std::forward<PRED>(pred));
        }

        template<__sImPlE_pReD_cOnCePt(PRED)>
        auto ClearUntilIf(OffsetType until, PRED&& pred) && -> ThisType {
            return T::ClearUntilIf(until, std::forward<PRED>(pred));
        }
    };
}

#endif //OBJECT_ARRAY_EA0E1E7F001A4C02ABA7367B15C9F753
