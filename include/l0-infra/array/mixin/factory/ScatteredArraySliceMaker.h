//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_9AA0AC630ECA4BFF9D0E43960D2A71D7
#define OBJECT_ARRAY_2_9AA0AC630ECA4BFF9D0E43960D2A71D7

#include <l0-infra/array/view/ScopeView.h>

namespace mixin {
    template<typename T>
    struct ScatteredArraySliceMaker : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto MakeSlice(SizeType num) & -> RefScopeView<ThisType> {
            return {T::ToThisType(), T::GetScope().GetLowestBits(num)};
        }

        auto MakeSlice(SizeType num) && -> ValueScopeView<ThisType> {
            return {T::ToThisType(), T::GetScope().GetLowestBits(num)};
        }
    };
}

#endif //OBJECT_ARRAY_2_9AA0AC630ECA4BFF9D0E43960D2A71D7
