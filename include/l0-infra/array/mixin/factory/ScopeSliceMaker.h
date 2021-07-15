//
// Created by Darwin Yuan on 2021/7/12.
//

#ifndef OBJECT_ARRAY_2_49B79B9F6B2D46A7801027FBC32E751E
#define OBJECT_ARRAY_2_49B79B9F6B2D46A7801027FBC32E751E

namespace mixin {
    template<typename T>
    struct ScopeSliceMaker : T {
        using typename T::SizeType;

    protected:
        using typename T::ThisType;

    public:
        auto MakeSlice(SizeType num)  -> ThisType {
            return {T::GetArray(), T::GetScope().GetLowestBits(num)};
        }
    };
}

#endif //OBJECT_ARRAY_2_49B79B9F6B2D46A7801027FBC32E751E
